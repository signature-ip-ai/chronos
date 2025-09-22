#ifndef __SN_NOC_TLM_IF_HPP__
#define __SN_NOC_TLM_IF_HPP__

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>

template<class SnIfxAdapter_t>
class SnNocTlmIf : public sc_core::sc_module
{
public:
    static constexpr auto BUS_WIDTH = SnIfxAdapter_t::BUS_WIDTH;
    using TYPES = typename SnIfxAdapter_t::TYPES;

    SC_HAS_PROCESS(SnNocTlmIf);
    SnNocTlmIf(sc_core::sc_module_name);

    tlm_utils::simple_initiator_socket<SnNocTlmIf, BUS_WIDTH, TYPES> initiator_socket;

protected:
    tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload&, tlm::tlm_phase&, sc_core::sc_time&);
    void invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range);
};

#endif  // __SN_NOC_TLM_IF_HPP__
