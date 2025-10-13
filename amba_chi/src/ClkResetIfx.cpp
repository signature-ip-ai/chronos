#include <ClkResetIfx.h>
#include <iostream>

ClkResetIfx::ClkResetIfx(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , main_clock_out("master_clk", 500, sc_core::SC_PS)
{
    rstb_out.write(true);

    SC_THREAD(initialize_system);

    std::cout << (const char*) name << " elaborated\n";
}

void ClkResetIfx::initialize_system()
{
    std::cout << "Intializing system\n";

    rstb_out.write(false);
    wait(sc_core::sc_time(2, sc_core::SC_NS));
    rstb_out.write(true);

    std::cout << "Intialized\n";
}
