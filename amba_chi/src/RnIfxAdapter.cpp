#include <RnIfxAdapter.h>
#include <iostream>

#include <ELinkState.h>
#include <RnIfxTracer.h>
#include <RnIfxAdapterTxChannel.h>

RnIfxAdapter::RnIfxAdapter(sc_core::sc_module_name module_name)
    : sc_core::sc_module(module_name)
    , target_socket()
    , tracer_(nullptr)
    , tx_channel_(std::make_shared<RnIfxAdapterTxChannel>("RnIfxAdapterTxChannel"))
    , rx_link_state_current_(ELinkState::STOP)
    , rx_link_state_next_(ELinkState::STOP)
{
    bind_tx_channels();
    tx_channel_->initialize();

    enable_trace();
    set_trace_time_unit(10, sc_core::SC_PS);

    target_socket.register_b_transport(this, &RnIfxAdapter::b_transport);
    target_socket.register_nb_transport_fw(this, &RnIfxAdapter::nb_transport_fw);
    target_socket.register_get_direct_mem_ptr(this, &RnIfxAdapter::get_direct_mem_ptr);
    target_socket.register_transport_dbg(this, &RnIfxAdapter::transport_dbg);

    SC_METHOD(forward_clock);
    sensitive << intfrx_clk_in;
    dont_initialize();

    SC_METHOD(forward_reset);
    sensitive << rstb_intfrx_clk_in;
    dont_initialize();

    std::cout << name() << " elaborated\n";
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

void RnIfxAdapter::rx_channel_adapter_reset()
{
    std::cout << name() << ": rx_channel_adapter_reset\n";

    // Required from CHI Rev E.b 14.1.3
    RX_LINKACTIVEACK_out.write(false);

    // All other states
    rx_link_state_current_ = ELinkState::STOP;
    rx_link_state_next_ = ELinkState::STOP;
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

void RnIfxAdapter::bind_tx_channels()
{
    tx_channel_->intfrx_clk_in(intfrx_clk_in);
    tx_channel_->rstb_intfrx_clk_in(rstb_intfrx_clk_in);

    tx_channel_->TXSACTIVE_out(TXSACTIVE_out);

    tx_channel_->TX_LINKACTIVEREQ_out(TX_LINKACTIVEREQ_out);
    tx_channel_->TX_LINKACTIVEACK_in(TX_LINKACTIVEACK_in);

    tx_channel_->TX_REQFLITPEND_out(TX_REQFLITPEND_out);
    tx_channel_->TX_REQFLITV_out(TX_REQFLITV_out);
    tx_channel_->TX_REQFLIT_out(TX_REQFLIT_out);
    tx_channel_->TX_REQLCRDV_in(TX_REQLCRDV_in);

    tx_channel_->TX_RSPFLITPEND_out(TX_RSPFLITPEND_out);
    tx_channel_->TX_RSPFLITV_out(TX_RSPFLITV_out);
    tx_channel_->TX_RSPFLIT_out(TX_RSPFLIT_out);
    tx_channel_->TX_RSPLCRDV_in(TX_RSPLCRDV_in);

    tx_channel_->TX_DATFLITPEND_out(TX_DATFLITPEND_out);
    tx_channel_->TX_DATFLITV_out(TX_DATFLITV_out);
    tx_channel_->TX_DATFLIT_out(TX_DATFLIT_out);
    tx_channel_->TX_DATLCRDV_in(TX_DATLCRDV_in);
}
