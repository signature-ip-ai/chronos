#ifndef __SN_IFX_ADAPTER__
#define __SN_IFX_ADAPTER__

#include <memory>
#include <systemc>
#include <tlm>

struct SnDeviceIf;

SC_MODULE(SnIfxAdapter)
{
public:
    SC_HAS_PROCESS(SnIfxAdapter);
    SnIfxAdapter(sc_core::sc_module_name name);

    std::shared_ptr<SnDeviceIf> sn_dev_if;
};

#endif  // __SN_IFX_ADAPTER__
