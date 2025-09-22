#ifndef __RN_DEVICE_IF_HXX__
#define __RN_DEVICE_IF_HXX__

#include <RnDeviceIf.h>

#include <type_traits>
#include <systemc>
#include <RnIfxAdapter.h>

template<class RnIfxAdapter_t>
RnDeviceIf<RnIfxAdapter_t>::RnDeviceIf(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
{
    static_assert(std::is_same<RnIfxAdapter_t, RnIfxAdapter>::value, "RnIfxAdapter_t must be of type RnIfxAdapter");
}

#endif  // __RN_DEVICE_IF_HXX__
