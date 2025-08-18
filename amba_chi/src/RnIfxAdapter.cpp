#include <RnIfxAdapter.hpp>

#include <memory>
#include <string>
#include <RnDeviceIf.hpp>
#include <RnNocTlmIf.hpp>

RnIfxAdapter::RnIfxAdapter(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
    , rn_dev_if(std::make_shared<RnDeviceIf>("RnDeviceIf0"))
    , rn_tlm_if(std::make_shared<RnNocTlmIf>("RnNocTlmIf0"))
    , target_socket(rn_tlm_if->target_socket)
{}
