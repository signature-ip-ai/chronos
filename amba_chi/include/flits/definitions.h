#ifndef __FLITS_DEFINITIONS_H__
#define __FLITS_DEFINITIONS_H__

#include <systemc>

namespace flits
{

static constexpr auto REQFLIT_WIDTH = 151;
static constexpr auto RSPFLIT_WIDTH = 73;
static constexpr auto DATFLIT_WIDTH = 680;
static constexpr auto SNPFLIT_WIDTH = 108;

using reqflit_t = sc_dt::sc_bv<REQFLIT_WIDTH>;
using rspflit_t = sc_dt::sc_bv<RSPFLIT_WIDTH>;
using datflit_t = sc_dt::sc_bv<DATFLIT_WIDTH>;
using snpflit_t = sc_dt::sc_bv<SNPFLIT_WIDTH>;

}  // namespace flits

#endif  // __FLITS_DEFINITIONS_H__
