#include <RnNocTlmIf.hpp>

#include <string>
#include <spdlog/spdlog.h>

RnNocTlmIf::RnNocTlmIf(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , target_socket("SimpleTargetSocket0")
{
    target_socket.register_b_transport(this, &RnNocTlmIf::b_transport);
    target_socket.register_nb_transport_fw(this, &RnNocTlmIf::nb_transport_fw);
    target_socket.register_get_direct_mem_ptr(this, &RnNocTlmIf::get_direct_mem_ptr);
    target_socket.register_transport_dbg(this, &RnNocTlmIf::transport_dbg);
}

void RnNocTlmIf::b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay)
{

}

tlm::tlm_sync_enum RnNocTlmIf::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_core::sc_time& delay)
{
    return tlm::tlm_sync_enum();
}

bool RnNocTlmIf::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
    return false;
}

unsigned int RnNocTlmIf::transport_dbg(tlm::tlm_generic_payload& trans)
{
    return 0;
}
