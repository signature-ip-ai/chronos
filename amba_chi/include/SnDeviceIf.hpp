#ifndef __SN_DEVICE_IF__
#define __SN_DEVICE_IF__

#include <systemc>
#include "BusWidthDefinitions.hpp"

struct SnDeviceIf
{
    using reqflit_t = sc_dt::sc_bv<REQFLIT_WIDTH>;
    using rspflit_t = sc_dt::sc_bv<RSPFLIT_WIDTH>;
    using datflit_t = sc_dt::sc_bv<DATFLIT_WIDTH>;

    SnDeviceIf() = default;
    SnDeviceIf(const SnDeviceIf&) = delete;
    SnDeviceIf& operator = (const SnDeviceIf&) = delete;
    SnDeviceIf(SnDeviceIf&&) = delete;
    SnDeviceIf& operator = (SnDeviceIf&&) = delete;

    // Reset and Clocking will be provided by the adapter
    sc_core::sc_out<bool> intfrx_clk;
    sc_core::sc_out<bool> rstb_intfrx_clk;

    sc_core::sc_out<bool> RX_LINKACTIVEREQ;
    sc_core::sc_in<bool> RX_LINKACTIVEACK;
    sc_core::sc_out<bool> RX_RSPFLITPEND;
    sc_core::sc_out<bool> RX_RSPFLITV;
    sc_core::sc_in<bool> RX_RSPLCRDV;
    sc_core::sc_out<bool> RX_DATFLITPEND;
    sc_core::sc_out<bool> RX_DATFLITV;
    sc_core::sc_in<bool> RX_DATLCRDV;
    sc_core::sc_in<bool> TX_LINKACTIVEREQ;
    sc_core::sc_out<bool> TX_LINKACTIVEACK;
    sc_core::sc_in<bool> TX_REQFLITPEND;
    sc_core::sc_in<bool> TX_REQFLITV;
    sc_core::sc_out<bool> TX_REQLCRDV;
    sc_core::sc_in<bool> TX_DATFLITPEND;
    sc_core::sc_in<bool> TX_DATFLITV;
    sc_core::sc_out<bool> TX_DATLCRDV;
    sc_core::sc_in<bool> TXSACTIVE;
    sc_core::sc_out<bool> RXSACTIVE;
    sc_core::sc_out<rspflit_t> RX_RSPFLIT;
    sc_core::sc_out<datflit_t> RX_DATFLIT;
    sc_core::sc_in<reqflit_t> TX_REQFLIT;
    sc_core::sc_in<datflit_t> TX_DATFLIT;
};

#endif  // __SN_DEVICE_IF__
