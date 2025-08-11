#ifndef __TLM2CA__
#define __TLM2CA__

#include <systemc>
#include <tlm>


class tlm2ca : public sc_core::sc_module
{
public:
    SC_HAS_PROCESS(tlm2ca);
    tlm2ca(sc_core::sc_module_name name);
};

#endif  // __TLM2CA__
