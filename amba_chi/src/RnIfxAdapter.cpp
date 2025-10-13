#include <RnIfxAdapter.h>
#include <iostream>

#include <ELinkState.h>


RnIfxAdapter::RnIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , target_socket()
    , tx_req_credit_counter_(0)
    , tx_dat_credit_counter_(0)
    , tx_rsp_credit_counter_(0)
    , tx_link_state_(ELinkState::STOP)
{
    target_socket.register_b_transport(this, &RnIfxAdapter::b_transport);
    target_socket.register_nb_transport_fw(this, &RnIfxAdapter::nb_transport_fw);
    target_socket.register_get_direct_mem_ptr(this, &RnIfxAdapter::get_direct_mem_ptr);
    target_socket.register_transport_dbg(this, &RnIfxAdapter::transport_dbg);

    adapter_reset();

    SC_METHOD(forward_clock);
    sensitive << intfrx_clk_in;
    dont_initialize();

    SC_METHOD(forward_reset);
    sensitive << rstb_intfrx_clk_in;
    dont_initialize();

    SC_METHOD(main_process);
    sensitive << intfrx_clk_in.pos() << rstb_intfrx_clk_in.neg();
    dont_initialize();

    std::cout << (const char*) name << " elaborated\n";
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

void RnIfxAdapter::main_process()
{
    if (!rstb_intfrx_clk_in.read())
    {
        adapter_reset();
        return;
    }

    tx_link_handshake();

    if (ELinkState::ACTIVATE == tx_link_state_)
    {
        tx_credit_check();
    }
}

void RnIfxAdapter::adapter_reset()
{
    std::cout << name() << ": adapter_reset\n";

    // Required from CHI Rev E.b 14.1.3
    TX_LINKACTIVEREQ_out.write(false);
    RX_LINKACTIVEACK_out.write(false);

    TX_REQFLITV_out.write(false);
    TX_DATFLITV_out.write(false);
    TX_RSPFLITV_out.write(false);

    // all other signals
    TX_REQFLITPEND_out.write(false);
    TX_RSPFLITPEND_out.write(false);
    TX_DATFLITPEND_out.write(false);

    tx_req_credit_counter_ = 0;
    tx_dat_credit_counter_ = 0;
    tx_rsp_credit_counter_ = 0;
    tx_link_state_ = ELinkState::STOP;
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
