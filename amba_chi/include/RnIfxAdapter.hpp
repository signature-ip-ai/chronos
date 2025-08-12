#ifndef __RN_ADAPTER__
#define __RN_ADAPTER__

#include <memory>
#include <systemc>
#include <tlm>

struct RnDeviceIf;

SC_MODULE(RnIfxAdapter)
{
public:
    SC_HAS_PROCESS(RnIfxAdapter);
    RnIfxAdapter(sc_core::sc_module_name name);

    std::shared_ptr<RnDeviceIf> rn_dev_if;
};

#endif  // __RN_ADAPTER__
