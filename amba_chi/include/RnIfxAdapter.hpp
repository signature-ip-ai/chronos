#ifndef __RN_IFX_ADAPTER_HPP__
#define __RN_IFX_ADAPTER_HPP__

#include <memory>
#include <systemc>
#include <tlm>
#include <tlm_utils/simple_target_socket.h>

template<class RnIfxAdapter_t>
struct RnDeviceIf;

template<class RnIfxAdapter_t>
struct RnNocTlmIf;

SC_MODULE(RnIfxAdapter)
{
public:
    static constexpr auto BUS_WIDTH = 32u;
    static constexpr auto REQFLIT_WIDTH = 151;
    static constexpr auto RSPFLIT_WIDTH = 73;
    static constexpr auto DATFLIT_WIDTH = 680;
    static constexpr auto SNPFLIT_WIDTH = 108;

    using TYPES = tlm::tlm_base_protocol_types;
    using reqflit_t = sc_dt::sc_bv<REQFLIT_WIDTH>;
    using rspflit_t = sc_dt::sc_bv<RSPFLIT_WIDTH>;
    using datflit_t = sc_dt::sc_bv<DATFLIT_WIDTH>;
    using snpflit_t = sc_dt::sc_bv<SNPFLIT_WIDTH>;

    SC_HAS_PROCESS(RnIfxAdapter);
    RnIfxAdapter(sc_core::sc_module_name name);

private:
    std::shared_ptr<RnDeviceIf<RnIfxAdapter>> rn_dev_if;
    std::shared_ptr<RnNocTlmIf<RnIfxAdapter>> rn_tlm_if;

public:
    tlm_utils::simple_target_socket<RnNocTlmIf<RnIfxAdapter>, BUS_WIDTH, TYPES>& target_socket;

    // Reset and Clocking will be provided by the adapter
    sc_core::sc_out<bool>& intfrx_clk;
    sc_core::sc_out<bool>& rstb_intfrx_clk;

    sc_core::sc_in<bool>& TX_LINKACTIVEREQ;
    sc_core::sc_out<bool>& TX_LINKACTIVEACK;
    sc_core::sc_out<bool>& RX_REQFLITPEND;
    sc_core::sc_out<bool>& RX_REQFLITV;
    sc_core::sc_in<bool>& RX_REQLCRDV;
    sc_core::sc_out<bool>& RX_RSPFLITPEND;
    sc_core::sc_out<bool>& RX_RSPFLITV;
    sc_core::sc_in<bool>& RX_RSPLCRDV;
    sc_core::sc_out<bool>& RX_DATFLITPEND;
    sc_core::sc_out<bool>& RX_DATFLITV;
    sc_core::sc_in<bool>& RX_DATLCRDV;
    sc_core::sc_out<bool>& RX_LINKACTIVEREQ;
    sc_core::sc_in<bool>& RX_LINKACTIVEACK;
    sc_core::sc_in<bool>& TX_SNPFLITPEND;
    sc_core::sc_in<bool>& TX_SNPFLITV;
    sc_core::sc_out<bool>& TX_SNPLCRDV;
    sc_core::sc_in<bool>& TX_RSPFLITPEND;
    sc_core::sc_in<bool>& TX_RSPFLITV;
    sc_core::sc_out<bool>& TX_RSPLCRDV;
    sc_core::sc_in<bool>& TX_DATFLITPEND;
    sc_core::sc_in<bool>& TX_DATFLITV;
    sc_core::sc_out<bool>& TX_DATLCRDV;
    sc_core::sc_in<bool>& TXSACTIVE;
    sc_core::sc_out<bool>& RXSACTIVE;
    sc_core::sc_out<bool>& SYSCOREQ;
    sc_core::sc_in<bool>& SYSCOACK;
    sc_core::sc_out<reqflit_t>& RX_REQFLIT;
    sc_core::sc_out<rspflit_t>& RX_RSPFLIT;
    sc_core::sc_out<datflit_t>& RX_DATFLIT;
    sc_core::sc_in<snpflit_t>& TX_SNPFLIT;
    sc_core::sc_in<rspflit_t>& TX_RSPFLIT;
    sc_core::sc_in<datflit_t>& TX_DATFLIT;
};

#endif  // __RN_IFX_ADAPTER_HPP__
