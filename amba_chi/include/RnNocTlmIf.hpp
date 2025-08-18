#ifndef __RN_NOC_TLM_IF__
#define __RN_NOC_TLM_IF__

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_target_socket.h>

SC_MODULE(RnNocTlmIf)
{
public:
    static constexpr auto BUS_WIDTH = 32u;
    using TYPES = tlm::tlm_base_protocol_types;

    SC_HAS_PROCESS(RnNocTlmIf);
    RnNocTlmIf(sc_core::sc_module_name);

    tlm_utils::simple_target_socket<RnNocTlmIf, BUS_WIDTH, TYPES> target_socket;

protected:
    void b_transport(tlm::tlm_generic_payload&, sc_core::sc_time&);
    tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload&, tlm::tlm_phase&, sc_core::sc_time&);
    bool get_direct_mem_ptr(tlm::tlm_generic_payload&, tlm::tlm_dmi&);
    unsigned int transport_dbg(tlm::tlm_generic_payload&);
};

#endif  // __RN_NOC_TLM_IF__
