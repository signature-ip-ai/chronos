#include <RnIfxAdapter.h>
#include <iostream>

#include <ELinkState.h>
#include <RnIfxTracer.h>

RnIfxAdapter::RnIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , target_socket()
    , tracer_(nullptr)
    , tx_req_credit_counter_(0)
    , tx_dat_credit_counter_(0)
    , tx_rsp_credit_counter_(0)
    , tx_link_state_(ELinkState::STOP)
    , rx_link_state_current_(ELinkState::STOP)
    , rx_link_state_next_(ELinkState::STOP)
{
    enable_trace();
    set_trace_time_unit(10, sc_core::SC_PS);

    target_socket.register_b_transport(this, &RnIfxAdapter::b_transport);
    target_socket.register_nb_transport_fw(this, &RnIfxAdapter::nb_transport_fw);
    target_socket.register_get_direct_mem_ptr(this, &RnIfxAdapter::get_direct_mem_ptr);
    target_socket.register_transport_dbg(this, &RnIfxAdapter::transport_dbg);

    tx_channel_adapter_reset();

    SC_METHOD(forward_clock);
    sensitive << intfrx_clk_in;
    dont_initialize();

    SC_METHOD(forward_reset);
    sensitive << rstb_intfrx_clk_in;
    dont_initialize();

    SC_METHOD(tx_channel_main_process);
    sensitive << intfrx_clk_in.pos() << rstb_intfrx_clk_in.neg();
    dont_initialize();

    std::cout << (const char*) name << " elaborated\n";
}

void RnIfxAdapter::enable_trace()
{
    tracer_ = std::make_shared<RnIfxTracer>(this, name());
}

void RnIfxAdapter::set_trace_time_unit(double value, sc_core::sc_time_unit time_unit)
{
    assert(tracer_ && "enable_trace must be called first before set_trace_time_unit(...)");
    tracer_->set_time_unit(value, time_unit);
}

void RnIfxAdapter::b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay)
{
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

tlm::tlm_sync_enum RnIfxAdapter::nb_transport_fw(
    tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_core::sc_time& delay)
{
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    return tlm::tlm_sync_enum();
}

bool RnIfxAdapter::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
    return false;
}

unsigned int RnIfxAdapter::transport_dbg(tlm::tlm_generic_payload& trans)
{
    return 0;
}

void RnIfxAdapter::forward_clock()
{
    intfrx_clk_out.write(intfrx_clk_in.read());
}

void RnIfxAdapter::forward_reset()
{
    rstb_intfrx_clk_out.write(rstb_intfrx_clk_in.read());
}

void RnIfxAdapter::tx_channel_main_process()
{
    if (!rstb_intfrx_clk_in.read())
    {
        tx_channel_adapter_reset();
        return;
    }

    tx_link_handshake();
    rx_link_handshake();

    if (ELinkState::ACTIVATE == tx_link_state_ || ELinkState::RUN == tx_link_state_)
    {
        tx_credit_check();
    }

    update_rx_link_state();
}

void RnIfxAdapter::tx_channel_adapter_reset()
{
    std::cout << name() << ": tx_channel_adapter_reset\n";

    // Required from CHI Rev E.b 14.1.3
    TX_LINKACTIVEREQ_out.write(false);

    TX_REQFLITV_out.write(false);
    TX_DATFLITV_out.write(false);
    TX_RSPFLITV_out.write(false);

    // all other signals
    TX_REQFLITPEND_out.write(false);
    TX_RSPFLITPEND_out.write(false);
    TX_DATFLITPEND_out.write(false);
    TXSACTIVE_out.write(false);

    tx_req_credit_counter_ = 0;
    tx_dat_credit_counter_ = 0;
    tx_rsp_credit_counter_ = 0;

    tx_link_state_ = ELinkState::STOP;
}

void RnIfxAdapter::rx_channel_adapter_reset()
{
    std::cout << name() << ": rx_channel_adapter_reset\n";

    // Required from CHI Rev E.b 14.1.3
    RX_LINKACTIVEACK_out.write(false);

    // All other states
    rx_link_state_current_ = ELinkState::STOP;
    rx_link_state_next_ = ELinkState::STOP;
}

void RnIfxAdapter::tx_credit_check()
{
    if ((MAX_CREDITS > tx_req_credit_counter_) && TX_REQLCRDV_in.read())
    {
        ++tx_req_credit_counter_;
        std::cout << "Increment tx_req_credit_counter_ " << tx_req_credit_counter_ << "\n";
    }

    if ((MAX_CREDITS > tx_dat_credit_counter_) && TX_DATLCRDV_in.read())
    {
        ++tx_dat_credit_counter_;
        std::cout << "Increment tx_dat_credit_counter_ " << tx_dat_credit_counter_ << "\n";
    }

    if ((MAX_CREDITS > tx_rsp_credit_counter_) && TX_RSPLCRDV_in.read())
    {
        ++tx_rsp_credit_counter_;
        std::cout << "Increment tx_rsp_credit_counter_ " << tx_rsp_credit_counter_ << "\n";
    }
}

void RnIfxAdapter::tx_link_handshake()
{
    if (!TXSACTIVE_out.read())
    {
        TXSACTIVE_out.write(true);
    }

    if (!TX_LINKACTIVEREQ_out.read())
    {
        TX_LINKACTIVEREQ_out.write(true);
        std::cout << "tx_link_handshake (ELinkState::ACTIVATE)\n";
        tx_link_state_ = ELinkState::ACTIVATE;
    }

    if (TX_LINKACTIVEREQ_out.read() and TX_LINKACTIVEACK_in.read())
    {
        std::cout << "tx_link_handshake (ELinkState::RUN)\n";
        tx_link_state_ = ELinkState::RUN;
    }
}

void RnIfxAdapter::rx_link_handshake()
{
    if (RXSACTIVE_in.read() && RX_LINKACTIVEREQ_in.read())
    {
        rx_link_state_next_ = ELinkState::ACTIVATE;
        std::cout << "rx_link_handshake (ELinkState::ACTIVATE)\n";
    }

    if (ELinkState::ACTIVATE == rx_link_state_current_)
    {
        RX_LINKACTIVEACK_out.write(true);
        rx_link_state_next_ = ELinkState::RUN;
        std::cout << "rx_link_handshake (ELinkState::RUN)\n";
    }
}

void RnIfxAdapter::update_rx_link_state()
{
    if (rx_link_state_current_ == rx_link_state_next_)
    {
        return;
    }

    rx_link_state_current_ = rx_link_state_next_;
}
