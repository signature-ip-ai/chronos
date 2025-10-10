#ifndef __RN_IFX_ADAPTER_H__
#define __RN_IFX_ADAPTER_H__

#include <systemc>
#include <tlm>
#include <tlm_utils/simple_target_socket.h>


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

    tlm_utils::simple_target_socket<RnIfxAdapter, BUS_WIDTH, TYPES> target_socket;

    // Reset and Clocking will be provided by ClkResetIfx
    sc_core::sc_in<bool> intfrx_clk_in;
    sc_core::sc_in<bool> rstb_intfrx_clk_in;

    // Reset and Clocking forwarded to the NoC RN interface
    sc_core::sc_signal<bool> intfrx_clk_out;
    sc_core::sc_signal<bool> rstb_intfrx_clk_out;

    sc_core::sc_signal<bool> TX_LINKACTIVEREQ_in;
    sc_core::sc_signal<bool> TX_LINKACTIVEACK_out;
    sc_core::sc_signal<bool> RX_REQFLITPEND_out;
    sc_core::sc_signal<bool> RX_REQFLITV_out;
    sc_core::sc_signal<bool> RX_REQLCRDV_in;
    sc_core::sc_signal<bool> RX_RSPFLITPEND_out;
    sc_core::sc_signal<bool> RX_RSPFLITV_out;
    sc_core::sc_signal<bool> RX_RSPLCRDV_in;
    sc_core::sc_signal<bool> RX_DATFLITPEND_out;
    sc_core::sc_signal<bool> RX_DATFLITV_out;
    sc_core::sc_signal<bool> RX_DATLCRDV_in;
    sc_core::sc_signal<bool> RX_LINKACTIVEREQ_out;
    sc_core::sc_signal<bool> RX_LINKACTIVEACK_in;
    sc_core::sc_signal<bool> TX_SNPFLITPEND_in;
    sc_core::sc_signal<bool> TX_SNPFLITV_in;
    sc_core::sc_signal<bool> TX_SNPLCRDV_out;
    sc_core::sc_signal<bool> TX_RSPFLITPEND_in;
    sc_core::sc_signal<bool> TX_RSPFLITV_in;
    sc_core::sc_signal<bool> TX_RSPLCRDV_out;
    sc_core::sc_signal<bool> TX_DATFLITPEND_in;
    sc_core::sc_signal<bool> TX_DATFLITV_in;
    sc_core::sc_signal<bool> TX_DATLCRDV_out;
    sc_core::sc_signal<bool> TXSACTIVE_in;
    sc_core::sc_signal<bool> RXSACTIVE_out;
    sc_core::sc_signal<bool> SYSCOREQ_out;
    sc_core::sc_signal<bool> SYSCOACK_in;
    sc_core::sc_signal<reqflit_t> RX_REQFLIT_out;
    sc_core::sc_signal<rspflit_t> RX_RSPFLIT_out;
    sc_core::sc_signal<datflit_t> RX_DATFLIT_out;
    sc_core::sc_signal<snpflit_t> TX_SNPFLIT_in;
    sc_core::sc_signal<rspflit_t> TX_RSPFLIT_in;
    sc_core::sc_signal<datflit_t> TX_DATFLIT_in;

private:
    void b_transport(tlm::tlm_generic_payload&, sc_core::sc_time&);
    tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload&, tlm::tlm_phase&, sc_core::sc_time&);
    bool get_direct_mem_ptr(tlm::tlm_generic_payload&, tlm::tlm_dmi&);
    unsigned int transport_dbg(tlm::tlm_generic_payload&);

    void forward_clock();
    void forward_reset();
};

#endif  // __RN_IFX_ADAPTER_H__
