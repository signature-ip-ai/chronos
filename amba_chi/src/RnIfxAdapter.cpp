#include <RnIfxAdapter.h>
#include <iostream>

RnIfxAdapter::RnIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , target_socket()
    , req_credit_counter_(0)
    , dat_credit_counter_(0)
    , rsp_credit_counter_(0)
{
    target_socket.register_b_transport(this, &RnIfxAdapter::b_transport);
    target_socket.register_nb_transport_fw(this, &RnIfxAdapter::nb_transport_fw);
    target_socket.register_get_direct_mem_ptr(this, &RnIfxAdapter::get_direct_mem_ptr);
    target_socket.register_transport_dbg(this, &RnIfxAdapter::transport_dbg);

    initialize_with_reset_state();

    SC_METHOD(forward_clock);
    sensitive << intfrx_clk_in;
    dont_initialize();

    SC_METHOD(forward_reset);
    sensitive << rstb_intfrx_clk_in;
    dont_initialize();

    SC_METHOD(initialize_with_reset_state);
    sensitive << rstb_intfrx_clk_in.neg();

    SC_METHOD(credit_check);
    sensitive << intfrx_clk_in.pos();

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

void RnIfxAdapter::initialize_with_reset_state()
{
    // Required from CHI Rev E.b 14.1.3
    TX_LINKACTIVEREQ_out.write(false);
    RX_LINKACTIVEACK_out.write(false);

    TX_REQFLITV_out.write(false);
    TX_DATFLITV_out.write(false);
    TX_RSPFLITV_out.write(false);

    // all other signals
    TX_REQFLITPEND_out.write(true);
    TX_RSPFLITPEND_out.write(true);
    TX_DATFLITPEND_out.write(true);
}

void RnIfxAdapter::credit_check()
{
    if (MAX_CREDITS > req_credit_counter_ && TX_REQLCRDV_in.read())
    {
        ++req_credit_counter_;
        std::cout << "Increment req_credit_counter_ " << req_credit_counter_ << "\n";
    }

    if (MAX_CREDITS > dat_credit_counter_ && TX_DATLCRDV_in.read())
    {
        ++dat_credit_counter_;
        std::cout << "Increment dat_credit_counter_ " << dat_credit_counter_ << "\n";
    }

    if (MAX_CREDITS > rsp_credit_counter_ && TX_RSPLCRDV_in.read())
    {
        ++rsp_credit_counter_;
        std::cout << "Increment rsp_credit_counter_ " << rsp_credit_counter_ << "\n";
    }
}
