#include <ClkResetIfx.h>

ClkResetIfx::ClkResetIfx(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , main_clock_out("master_clk", 500, sc_core::SC_PS)
{}
