#ifndef __SN_DEVICE_IF_HXX__
#define __SN_DEVICE_IF_HXX__

#include <SnDeviceIf.h>

#include <type_traits>
#include <systemc>
#include <SnIfxAdapter.h>

template<class SnIfxAdapter_t>
SnDeviceIf<SnIfxAdapter_t>::SnDeviceIf(sc_core::sc_module_name name)
    : sc_core::sc_module(name)
{
    static_assert(std::is_same<SnIfxAdapter_t, SnIfxAdapter>::value, "SnIfxAdapter_t must be of type SnIfxAdapter");
}

#endif  // __SN_DEVICE_IF_HXX__
