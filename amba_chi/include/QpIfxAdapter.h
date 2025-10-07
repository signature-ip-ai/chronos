#ifndef __QP_IFX_ADAPTER_H__
#define __QP_IFX_ADAPTER_H__

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_target_socket.h>


SC_MODULE(QpIfxAdapter)
{
public:
    static constexpr auto BUS_WIDTH = 32u;
    using TYPES = tlm::tlm_base_protocol_types;

    SC_HAS_PROCESS(QpIfxAdapter);
    QpIfxAdapter(sc_core::sc_module_name name);

    tlm_utils::simple_target_socket<QpIfxAdapter, BUS_WIDTH, TYPES> target_socket;

    sc_core::sc_signal<bool> qp_clk_out;
    sc_core::sc_signal<bool> qp_rstb_out;
    sc_core::sc_signal<bool> qreqn_out;
    sc_core::sc_signal<bool> qacceptn_in;
    sc_core::sc_signal<bool> qdeny_in;
    sc_core::sc_signal<bool> qactive_in;
    sc_core::sc_signal<bool> qin_quiescence_in;
    sc_core::sc_signal<bool> pstate_out;
    sc_core::sc_signal<bool> preq_out;
    sc_core::sc_signal<bool> paccept_in;
    sc_core::sc_signal<bool> pdeny_in;
    sc_core::sc_signal<bool> pactive_in;

private:
    void b_transport(tlm::tlm_generic_payload&, sc_core::sc_time&);
    tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload&, tlm::tlm_phase&, sc_core::sc_time&);
    bool get_direct_mem_ptr(tlm::tlm_generic_payload&, tlm::tlm_dmi&);
    unsigned int transport_dbg(tlm::tlm_generic_payload&);
};

#endif  // __QP_IFX_ADAPTER_H__
