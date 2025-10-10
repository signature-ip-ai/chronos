#ifndef __PROG_IFX_ADAPTER_H__
#define __PROG_IFX_ADAPTER_H__

#include <systemc>


SC_MODULE(ProgIfxAdapter)
{
public:
    SC_HAS_PROCESS(ProgIfxAdapter);
    ProgIfxAdapter(sc_core::sc_module_name name);

    sc_core::sc_signal<bool> PCLK_prog_out;
    sc_core::sc_signal<bool> PRESETn_prog_out;
    sc_core::sc_signal<bool> PSEL_prog_out;
    sc_core::sc_signal<bool> PENABLE_prog_out;
    sc_core::sc_signal<bool> PWRITE_prog_out;
    sc_core::sc_signal<uint32_t> PSTRB_prog_out;
    sc_core::sc_signal<bool> PREADY_prog_in;
    sc_core::sc_signal<bool> PSLVERR_prog_in;
    sc_core::sc_signal<uint32_t> PADDR_prog_out;
    sc_core::sc_signal<uint32_t> PWDATA_prog_out;
    sc_core::sc_signal<uint32_t> PRDATA_prog_in;
};

#endif  // __PROG_IFX_ADAPTER_H__
