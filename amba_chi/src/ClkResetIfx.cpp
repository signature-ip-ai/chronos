#include <ClkResetIfx.h>
#include <iostream>

ClkResetIfx::ClkResetIfx(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , main_clock_out("master_clk", 500, sc_core::SC_PS)
{
    rstb_out.write(true);

    std::cout << (const char*) name << " elaborated\n";
}
