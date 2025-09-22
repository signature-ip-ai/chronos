#ifndef __RN_DEVICE_IF_HPP__
#define __RN_DEVICE_IF_HPP__

#include <type_traits>
#include <systemc>

template<class RnIfxAdapter_t>
class RnDeviceIf : public sc_core::sc_module
{
public:
    using reqflit_t = typename RnIfxAdapter_t::reqflit_t;
    using rspflit_t = typename RnIfxAdapter_t::rspflit_t;
    using datflit_t = typename RnIfxAdapter_t::datflit_t;
    using snpflit_t = typename RnIfxAdapter_t::snpflit_t;

    SC_HAS_PROCESS(RnDeviceIf);
    RnDeviceIf(sc_core::sc_module_name);

    // Reset and Clocking will be provided by the adapter
    sc_core::sc_out<bool> intfrx_clk;
    sc_core::sc_out<bool> rstb_intfrx_clk;

    sc_core::sc_in<bool> TX_LINKACTIVEREQ;
    sc_core::sc_out<bool> TX_LINKACTIVEACK;
    sc_core::sc_out<bool> RX_REQFLITPEND;
    sc_core::sc_out<bool> RX_REQFLITV;
    sc_core::sc_in<bool> RX_REQLCRDV;
    sc_core::sc_out<bool> RX_RSPFLITPEND;
    sc_core::sc_out<bool> RX_RSPFLITV;
    sc_core::sc_in<bool> RX_RSPLCRDV;
    sc_core::sc_out<bool> RX_DATFLITPEND;
    sc_core::sc_out<bool> RX_DATFLITV;
    sc_core::sc_in<bool> RX_DATLCRDV;
    sc_core::sc_out<bool> RX_LINKACTIVEREQ;
    sc_core::sc_in<bool> RX_LINKACTIVEACK;
    sc_core::sc_in<bool> TX_SNPFLITPEND;
    sc_core::sc_in<bool> TX_SNPFLITV;
    sc_core::sc_out<bool> TX_SNPLCRDV;
    sc_core::sc_in<bool> TX_RSPFLITPEND;
    sc_core::sc_in<bool> TX_RSPFLITV;
    sc_core::sc_out<bool> TX_RSPLCRDV;
    sc_core::sc_in<bool> TX_DATFLITPEND;
    sc_core::sc_in<bool> TX_DATFLITV;
    sc_core::sc_out<bool> TX_DATLCRDV;
    sc_core::sc_in<bool> TXSACTIVE;
    sc_core::sc_out<bool> RXSACTIVE;
    sc_core::sc_out<bool> SYSCOREQ;
    sc_core::sc_in<bool> SYSCOACK;
    sc_core::sc_out<reqflit_t> RX_REQFLIT;
    sc_core::sc_out<rspflit_t> RX_RSPFLIT;
    sc_core::sc_out<datflit_t> RX_DATFLIT;
    sc_core::sc_in<snpflit_t> TX_SNPFLIT;
    sc_core::sc_in<rspflit_t> TX_RSPFLIT;
    sc_core::sc_in<datflit_t> TX_DATFLIT;
};

#endif  // __RN_DEVICE_IF_HPP__
