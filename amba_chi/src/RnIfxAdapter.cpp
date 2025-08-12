#include <RnIfxAdapter.hpp>

#include <memory>
#include <RnDeviceIf.hpp>

RnIfxAdapter::RnIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , rn_dev_if(std::make_shared<RnDeviceIf>())
{}
