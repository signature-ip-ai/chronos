#ifndef __SN_NOC_TLM_IF_HXX__
#define __SN_NOC_TLM_IF_HXX__

#include <SnNocTlmIf.hpp>

#include <type_traits>
#include <systemc>
#include <SnIfxAdapter.hpp>

template<class SnIfxAdapter_t>
SnNocTlmIf<SnIfxAdapter_t>::SnNocTlmIf(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , initiator_socket("SimpleInitiatorSocket0")
{
    static_assert(std::is_same<SnIfxAdapter_t, SnIfxAdapter>::value, "SnIfxAdapter_t must be of type SnIfxAdapter");
    initiator_socket.register_nb_transport_bw(this, &SnNocTlmIf<SnIfxAdapter_t>::nb_transport_bw);
    initiator_socket.register_invalidate_direct_mem_ptr(this, &SnNocTlmIf<SnIfxAdapter_t>::invalidate_direct_mem_ptr);
}

template<class SnIfxAdapter_t>
tlm::tlm_sync_enum SnNocTlmIf<SnIfxAdapter_t>::nb_transport_bw(
    tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_core::sc_time& delay)
{
    return tlm::tlm_sync_enum();
}

template<class SnIfxAdapter_t>
void SnNocTlmIf<SnIfxAdapter_t>::invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range)
{
}

#endif  // __SN_NOC_TLM_IF_HXX__
