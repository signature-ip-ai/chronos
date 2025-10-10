#ifndef __QP_IFX_ADAPTER_H__
#define __QP_IFX_ADAPTER_H__

#include <systemc>


SC_MODULE(QpIfxAdapter)
{
public:
    SC_HAS_PROCESS(QpIfxAdapter);
    QpIfxAdapter(sc_core::sc_module_name name);

    // Reset and Clocking will be provided by ClkResetIfx
    sc_core::sc_in<bool> qp_clk_in;
    sc_core::sc_in<bool> qp_rstb_in;

    // Reset and Clocking forwarded to the NoC QP interface
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

    void forward_clock();
    void forward_reset();
};

#endif  // __QP_IFX_ADAPTER_H__
