#ifndef __RN_NOC_TLM_IF_HPP__
#define __RN_NOC_TLM_IF_HPP__

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_target_socket.h>

template<class RnIfxAdapter_t>
class RnNocTlmIf : public sc_core::sc_module
{
public:
    static constexpr auto BUS_WIDTH = RnIfxAdapter_t::BUS_WIDTH;
    using TYPES = typename RnIfxAdapter_t::TYPES;

    SC_HAS_PROCESS(RnNocTlmIf);
    RnNocTlmIf(sc_core::sc_module_name);

    tlm_utils::simple_target_socket<RnNocTlmIf, BUS_WIDTH, TYPES> target_socket;

protected:
    void b_transport(tlm::tlm_generic_payload&, sc_core::sc_time&);
    tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload&, tlm::tlm_phase&, sc_core::sc_time&);
    bool get_direct_mem_ptr(tlm::tlm_generic_payload&, tlm::tlm_dmi&);
    unsigned int transport_dbg(tlm::tlm_generic_payload&);
};

#endif  // __RN_NOC_TLM_IF_HPP__
