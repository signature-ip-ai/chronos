#ifndef __CLK_RESET_IFX_H__
#define __CLK_RESET_IFX_H__

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_target_socket.h>


SC_MODULE(ClkResetIfx)
{
public:
    SC_HAS_PROCESS(ClkResetIfx);
    ClkResetIfx(sc_core::sc_module_name name);

    sc_core::sc_clock main_clock_out;
    sc_core::sc_signal<bool> rstb_ic_clk_out;
    sc_core::sc_signal<bool> cc_rstb_intfrx_clk_out;
};

#endif  // __CLK_RESET_IFX_H__
