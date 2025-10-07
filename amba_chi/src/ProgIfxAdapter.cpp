#include <ProgIfxAdapter.h>

ProgIfxAdapter::ProgIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , target_socket()
{
    target_socket.register_b_transport(this, &ProgIfxAdapter::b_transport);
    target_socket.register_nb_transport_fw(this, &ProgIfxAdapter::nb_transport_fw);
    target_socket.register_get_direct_mem_ptr(this, &ProgIfxAdapter::get_direct_mem_ptr);
    target_socket.register_transport_dbg(this, &ProgIfxAdapter::transport_dbg);
}

void ProgIfxAdapter::b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay)
{
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

tlm::tlm_sync_enum ProgIfxAdapter::nb_transport_fw(
    tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_core::sc_time& delay)
{
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    return tlm::tlm_sync_enum();
}

bool ProgIfxAdapter::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
    return false;
}

unsigned int ProgIfxAdapter::transport_dbg(tlm::tlm_generic_payload& trans)
{
    return 0;
}
