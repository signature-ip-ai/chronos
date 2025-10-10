#include <RnIfxAdapter.h>

RnIfxAdapter::RnIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , target_socket()
{
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
