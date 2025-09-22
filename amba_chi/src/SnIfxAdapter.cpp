#include <SnIfxAdapter.h>

#include <memory>
#include <systemc>
#include <SnDeviceIf.hxx>
#include <SnNocTlmIf.hxx>

SnIfxAdapter::SnIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
{
    initiator_socket.register_nb_transport_bw(this, &SnIfxAdapter::nb_transport_bw);
    initiator_socket.register_invalidate_direct_mem_ptr(this, &SnIfxAdapter::invalidate_direct_mem_ptr);
}

tlm::tlm_sync_enum SnIfxAdapter::nb_transport_bw(
    tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_core::sc_time& delay)
{
    return tlm::tlm_sync_enum();
}

void SnIfxAdapter::invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range)
{}
