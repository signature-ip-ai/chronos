#ifndef __SIMPLE_INITIATOR_H__
#define __SIMPLE_INITIATOR_H__

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>


class SimpleInitiator : public sc_core::sc_module
{
public:
    tlm_utils::simple_initiator_socket<SimpleInitiator> initiator_socket;

    SC_CTOR(SimpleInitiator) : initiator_socket("socket")
    {
        SC_THREAD(stimulus_process);
        initiator_socket.register_nb_transport_bw(this, &SimpleInitiator::nb_transport_bw);
        initiator_socket.register_invalidate_direct_mem_ptr(this, &SimpleInitiator::invalidate_direct_mem_ptr);
    }

private:
    void stimulus_process()
    {}

    tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload& trans,
                                     tlm::tlm_phase& phase,
                                     sc_core::sc_time& delay)
    {
        return tlm::TLM_COMPLETED;
    }

    void invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                 sc_dt::uint64 end_range)
    {
    }
};

#endif  // __SIMPLE_INITIATOR_H__
