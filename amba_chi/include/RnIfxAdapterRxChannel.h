#ifndef __RN_IFX_ADAPTER_RX_CHANNEL_H__
#define __RN_IFX_ADAPTER_RX_CHANNEL_H__

#include <systemc>
#include <flits/definitions.h>

enum class ELinkState;

SC_MODULE(RnIfxAdapterRxChannel)
{
public:
    static constexpr auto MAX_CREDITS = 15u;

    RnIfxAdapterRxChannel(sc_core::sc_module_name name);

    sc_core::sc_in<bool> intfrx_clk_in;
    sc_core::sc_in<bool> rstb_intfrx_clk_in;

    sc_core::sc_in<bool> RXSACTIVE_in;

    sc_core::sc_in<bool> RX_LINKACTIVEREQ_in;
    sc_core::sc_out<bool> RX_LINKACTIVEACK_out;

    sc_core::sc_in<bool> RX_RSPFLITPEND_in;
    sc_core::sc_in<bool> RX_RSPFLITV_in;
    sc_core::sc_in<flits::rspflit_t> RX_RSPFLIT_in;
    sc_core::sc_out<bool> RX_RSPLCRDV_out;

    sc_core::sc_in<bool> RX_DATFLITPEND_in;
    sc_core::sc_in<bool> RX_DATFLITV_in;
    sc_core::sc_in<flits::datflit_t> RX_DATFLIT_in;
    sc_core::sc_out<bool> RX_DATLCRDV_out;

    sc_core::sc_in<bool> RX_SNPFLITPEND_in;
    sc_core::sc_in<bool> RX_SNPFLITV_in;
    sc_core::sc_in<flits::snpflit_t> RX_SNPFLIT_in;
    sc_core::sc_out<bool> RX_SNPLCRDV_out;

    void initialize();

private:
    void main_process();
    void reset();
    void link_handshake();
    void credit_send();
    void update_link_state();

    bool module_initialized_;

    uint8_t req_credit_available_;
    uint8_t dat_credit_available_;
    uint8_t rsp_credit_available_;

    ELinkState link_state_current_;
    ELinkState link_state_next_;
};

#endif  // __RN_IFX_ADAPTER_RX_CHANNEL_H__
