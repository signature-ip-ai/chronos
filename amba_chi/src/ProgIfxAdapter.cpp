#include <ProgIfxAdapter.h>

ProgIfxAdapter::ProgIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
{
    PSEL_prog_out.write(false);
    PENABLE_prog_out.write(false);
    PWRITE_prog_out.write(false);
    PRESETn_prog_out.write(true);
    PSTRB_prog_out.write(0);
    PADDR_prog_out.write(0);
    PWDATA_prog_out.write(0);

    SC_METHOD(forward_clock);
    sensitive << PCLK_prog_in;
    dont_initialize();

    SC_METHOD(forward_reset);
    sensitive << PRESETn_prog_in;
    dont_initialize();
}

void ProgIfxAdapter::forward_clock()
{
    PCLK_prog_out.write(PCLK_prog_in.read());
}

void ProgIfxAdapter::forward_reset()
{
    PRESETn_prog_out.write(PRESETn_prog_in.read());
}
