#ifndef __RN_NOC_TLM_IF_HXX__
#define __RN_NOC_TLM_IF_HXX__

#include <RnNocTlmIf.hpp>

#include <type_traits>
#include <systemc>
#include <RnIfxAdapter.hpp>

template<class RnIfxAdapter_t>
RnNocTlmIf<RnIfxAdapter_t>::RnNocTlmIf(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , target_socket("SimpleTargetSocket0")
{
    static_assert(std::is_same<RnIfxAdapter_t, RnIfxAdapter>::value, "RnIfxAdapter_t must be of type RnIfxAdapter");
    target_socket.register_b_transport(this, &RnNocTlmIf<RnIfxAdapter_t>::b_transport);
    target_socket.register_nb_transport_fw(this, &RnNocTlmIf<RnIfxAdapter_t>::nb_transport_fw);
    target_socket.register_get_direct_mem_ptr(this, &RnNocTlmIf<RnIfxAdapter_t>::get_direct_mem_ptr);
    target_socket.register_transport_dbg(this, &RnNocTlmIf<RnIfxAdapter_t>::transport_dbg);
}

template<class RnIfxAdapter_t>
void RnNocTlmIf<RnIfxAdapter_t>::b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay)
{

}

template<class RnIfxAdapter_t>
tlm::tlm_sync_enum RnNocTlmIf<RnIfxAdapter_t>::nb_transport_fw(
    tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_core::sc_time& delay)
{
    return tlm::tlm_sync_enum();
}

template<class RnIfxAdapter_t>
bool RnNocTlmIf<RnIfxAdapter_t>::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
    return false;
}

template<class RnIfxAdapter_t>
unsigned int RnNocTlmIf<RnIfxAdapter_t>::transport_dbg(tlm::tlm_generic_payload& trans)
{
    return 0;
}

#endif  // __RN_NOC_TLM_IF_HXX__
