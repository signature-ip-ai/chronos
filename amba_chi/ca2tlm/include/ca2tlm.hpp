#ifndef __CA2TLM__
#define __CA2TLM__

#include <systemc>
#include <tlm>


class ca2tlm : public sc_core::sc_module
{
public:
    SC_HAS_PROCESS(ca2tlm);
    ca2tlm(sc_core::sc_module_name name);
};

#endif  // __CA2TLM__
