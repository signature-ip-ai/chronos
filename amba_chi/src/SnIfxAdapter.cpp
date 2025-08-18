#include <SnIfxAdapter.hpp>

#include <systemc>
#include <SnDeviceIf.hpp>

SnIfxAdapter::SnIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , sn_dev_if(std::make_shared<SnDeviceIf>())
{
}
