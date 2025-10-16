#ifndef __RN_IFX_ADAPTER_TX_CHANNEL_H__
#define __RN_IFX_ADAPTER_TX_CHANNEL_H__

#include <systemc>
#include <flits/definitions.h>

enum class ELinkState;

SC_MODULE(RnIfxAdapterTxChannel)
{
public:
    static constexpr auto MAX_CREDITS = 15u;

    RnIfxAdapterTxChannel(sc_core::sc_module_name name);

    sc_core::sc_in<bool> intfrx_clk_in;
    sc_core::sc_in<bool> rstb_intfrx_clk_in;

    sc_core::sc_out<bool> TXSACTIVE_out;

    sc_core::sc_out<bool> TX_LINKACTIVEREQ_out;
    sc_core::sc_in<bool> TX_LINKACTIVEACK_in;

    sc_core::sc_out<bool> TX_REQFLITPEND_out;
    sc_core::sc_out<bool> TX_REQFLITV_out;
    sc_core::sc_out<flits::reqflit_t> TX_REQFLIT_out;
    sc_core::sc_in<bool> TX_REQLCRDV_in;

    sc_core::sc_out<bool> TX_RSPFLITPEND_out;
    sc_core::sc_out<bool> TX_RSPFLITV_out;
    sc_core::sc_out<flits::rspflit_t> TX_RSPFLIT_out;
    sc_core::sc_in<bool> TX_RSPLCRDV_in;

    sc_core::sc_out<bool> TX_DATFLITPEND_out;
    sc_core::sc_out<bool> TX_DATFLITV_out;
    sc_core::sc_out<flits::datflit_t> TX_DATFLIT_out;
    sc_core::sc_in<bool> TX_DATLCRDV_in;

    void initialize();

private:
    void main_process();
    void reset();
    void link_handshake();
    void credit_check();
    void update_link_state();

    bool module_initialized_;

    uint8_t req_credit_counter_;
    uint8_t dat_credit_counter_;
    uint8_t rsp_credit_counter_;

    ELinkState link_state_current_;
    ELinkState link_state_next_;
};

#endif  // __RN_IFX_ADAPTER_TX_CHANNEL_H__
