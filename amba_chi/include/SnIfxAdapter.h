#ifndef __SN_IFX_ADAPTER_HPP__
#define __SN_IFX_ADAPTER_HPP__

#include <memory>
#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>

template<class SnIfxAdapter_t>
struct SnDeviceIf;

template<class SnIfxAdapter_t>
struct SnNocTlmIf;

SC_MODULE(SnIfxAdapter)
{
public:
    static constexpr auto BUS_WIDTH = 32u;
    static constexpr auto REQFLIT_WIDTH = 151;
    static constexpr auto RSPFLIT_WIDTH = 73;
    static constexpr auto DATFLIT_WIDTH = 680;

    using TYPES = tlm::tlm_base_protocol_types;
    using reqflit_t = sc_dt::sc_bv<REQFLIT_WIDTH>;
    using rspflit_t = sc_dt::sc_bv<RSPFLIT_WIDTH>;
    using datflit_t = sc_dt::sc_bv<DATFLIT_WIDTH>;

    SC_HAS_PROCESS(SnIfxAdapter);
    SnIfxAdapter(sc_core::sc_module_name name);

private:
    std::shared_ptr<SnDeviceIf<SnIfxAdapter>> sn_dev_if;
    std::shared_ptr<SnNocTlmIf<SnIfxAdapter>> sn_tlm_if;

public:
    tlm_utils::simple_initiator_socket<SnNocTlmIf<SnIfxAdapter>, BUS_WIDTH, TYPES>& initiator_socket;

    // Reset and Clocking will be provided by the adapter
    sc_core::sc_out<bool>& intfrx_clk;
    sc_core::sc_out<bool>& rstb_intfrx_clk;

    sc_core::sc_out<bool>& RX_LINKACTIVEREQ;
    sc_core::sc_in<bool>& RX_LINKACTIVEACK;
    sc_core::sc_out<bool>& RX_RSPFLITPEND;
    sc_core::sc_out<bool>& RX_RSPFLITV;
    sc_core::sc_in<bool>& RX_RSPLCRDV;
    sc_core::sc_out<bool>& RX_DATFLITPEND;
    sc_core::sc_out<bool>& RX_DATFLITV;
    sc_core::sc_in<bool>& RX_DATLCRDV;
    sc_core::sc_in<bool>& TX_LINKACTIVEREQ;
    sc_core::sc_out<bool>& TX_LINKACTIVEACK;
    sc_core::sc_in<bool>& TX_REQFLITPEND;
    sc_core::sc_in<bool>& TX_REQFLITV;
    sc_core::sc_out<bool>& TX_REQLCRDV;
    sc_core::sc_in<bool>& TX_DATFLITPEND;
    sc_core::sc_in<bool>& TX_DATFLITV;
    sc_core::sc_out<bool>& TX_DATLCRDV;
    sc_core::sc_in<bool>& TXSACTIVE;
    sc_core::sc_out<bool>& RXSACTIVE;
    sc_core::sc_out<rspflit_t>& RX_RSPFLIT;
    sc_core::sc_out<datflit_t>& RX_DATFLIT;
    sc_core::sc_in<reqflit_t>& TX_REQFLIT;
    sc_core::sc_in<datflit_t>& TX_DATFLIT;
};

#endif  // __SN_IFX_ADAPTER_HPP__
