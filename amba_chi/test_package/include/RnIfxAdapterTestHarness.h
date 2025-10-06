#ifndef __RN_IFXADAPTER_TEST_HARNESS_H__
#define __RN_IFXADAPTER_TEST_HARNESS_H__

#include <memory>
#include <systemc>

#include <RnIfxAdapter.h>
#include <SimpleInitiator.h>


struct RnIfxAdapterTestHarness
{
    RnIfxAdapterTestHarness()
        : initiator(std::make_shared<SimpleInitiator>("SimpleInitiator"))
        , rnAdapter(std::make_shared<RnIfxAdapter>("RnIfxAdapter"))
    {
        bind_all_ports();
        initialize_unused_inputs();
        spdlog::info("Target Socket Name: {:s}", rnAdapter->target_socket.name());
        initiator->initiator_socket.bind(rnAdapter->target_socket);
    }

    void bind_all_ports()
    {
        // Interface clocks (outputs)
        rnAdapter->intfrx_clk(intfrx_clk_sig);
        rnAdapter->rstb_intfrx_clk(rstb_intfrx_clk_sig);

        // Link activation
        rnAdapter->TX_LINKACTIVEREQ(TX_LINKACTIVEREQ_sig);
        rnAdapter->TX_LINKACTIVEACK(TX_LINKACTIVEACK_sig);
        rnAdapter->RX_LINKACTIVEREQ(RX_LINKACTIVEREQ_sig);
        rnAdapter->RX_LINKACTIVEACK(RX_LINKACTIVEACK_sig);

        // RX channels
        rnAdapter->RX_REQFLITPEND(RX_REQFLITPEND_sig);
        rnAdapter->RX_REQFLITV(RX_REQFLITV_sig);
        rnAdapter->RX_REQLCRDV(RX_REQLCRDV_sig);
        rnAdapter->RX_REQFLIT(RX_REQFLIT_sig);

        rnAdapter->RX_RSPFLITPEND(RX_RSPFLITPEND_sig);
        rnAdapter->RX_RSPFLITV(RX_RSPFLITV_sig);
        rnAdapter->RX_RSPLCRDV(RX_RSPLCRDV_sig);
        rnAdapter->RX_RSPFLIT(RX_RSPFLIT_sig);

        rnAdapter->RX_DATFLITPEND(RX_DATFLITPEND_sig);
        rnAdapter->RX_DATFLITV(RX_DATFLITV_sig);
        rnAdapter->RX_DATLCRDV(RX_DATLCRDV_sig);
        rnAdapter->RX_DATFLIT(RX_DATFLIT_sig);

        // TX channels
        rnAdapter->TX_SNPFLITPEND(TX_SNPFLITPEND_sig);
        rnAdapter->TX_SNPFLITV(TX_SNPFLITV_sig);
        rnAdapter->TX_SNPLCRDV(TX_SNPLCRDV_sig);
        rnAdapter->TX_SNPFLIT(TX_SNPFLIT_sig);

        rnAdapter->TX_RSPFLITPEND(TX_RSPFLITPEND_sig);
        rnAdapter->TX_RSPFLITV(TX_RSPFLITV_sig);
        rnAdapter->TX_RSPLCRDV(TX_RSPLCRDV_sig);
        rnAdapter->TX_RSPFLIT(TX_RSPFLIT_sig);

        rnAdapter->TX_DATFLITPEND(TX_DATFLITPEND_sig);
        rnAdapter->TX_DATFLITV(TX_DATFLITV_sig);
        rnAdapter->TX_DATLCRDV(TX_DATLCRDV_sig);
        rnAdapter->TX_DATFLIT(TX_DATFLIT_sig);

        // System signals
        rnAdapter->TXSACTIVE(TXSACTIVE_sig);
        rnAdapter->RXSACTIVE(RXSACTIVE_sig);
        rnAdapter->SYSCOREQ(SYSCOREQ_sig);
        rnAdapter->SYSCOACK(SYSCOACK_sig);
    }

    void initialize_unused_inputs() {
        TX_LINKACTIVEREQ_sig.write(false);
        RX_REQLCRDV_sig.write(true);
        RX_RSPLCRDV_sig.write(true);
        RX_DATLCRDV_sig.write(true);
        RX_LINKACTIVEACK_sig.write(false);

        // TX channel inputs (from network)
        TX_SNPFLITPEND_sig.write(false);
        TX_SNPFLITV_sig.write(false);
        TX_RSPFLITPEND_sig.write(false);
        TX_RSPFLITV_sig.write(false);
        TX_DATFLITPEND_sig.write(false);
        TX_DATFLITV_sig.write(false);

        // System signals
        TXSACTIVE_sig.write(false);
        SYSCOACK_sig.write(false);

        // Initialize flit data to zero/default values
        TX_SNPFLIT_sig.write(RnIfxAdapter::snpflit_t{});
        TX_RSPFLIT_sig.write(RnIfxAdapter::rspflit_t{});
        TX_DATFLIT_sig.write(RnIfxAdapter::datflit_t{});
    }

    std::shared_ptr<SimpleInitiator> initiator;
    std::shared_ptr<RnIfxAdapter> rnAdapter;

    // Interface clock signals (outputs from rnAdapter)
    sc_core::sc_signal<bool> intfrx_clk_sig;
    sc_core::sc_signal<bool> rstb_intfrx_clk_sig;

    // Link activation signals
    sc_core::sc_signal<bool> TX_LINKACTIVEREQ_sig;
    sc_core::sc_signal<bool> TX_LINKACTIVEACK_sig;
    sc_core::sc_signal<bool> RX_LINKACTIVEREQ_sig;
    sc_core::sc_signal<bool> RX_LINKACTIVEACK_sig;

    // RX channel signals (REQ)
    sc_core::sc_signal<bool> RX_REQFLITPEND_sig;
    sc_core::sc_signal<bool> RX_REQFLITV_sig;
    sc_core::sc_signal<bool> RX_REQLCRDV_sig;
    sc_core::sc_signal<RnIfxAdapter::reqflit_t> RX_REQFLIT_sig;

    // RX channel signals (RSP)
    sc_core::sc_signal<bool> RX_RSPFLITPEND_sig;
    sc_core::sc_signal<bool> RX_RSPFLITV_sig;
    sc_core::sc_signal<bool> RX_RSPLCRDV_sig;
    sc_core::sc_signal<RnIfxAdapter::rspflit_t> RX_RSPFLIT_sig;

    // RX channel signals (DAT)
    sc_core::sc_signal<bool> RX_DATFLITPEND_sig;
    sc_core::sc_signal<bool> RX_DATFLITV_sig;
    sc_core::sc_signal<bool> RX_DATLCRDV_sig;
    sc_core::sc_signal<RnIfxAdapter::datflit_t> RX_DATFLIT_sig;

    // TX channel signals (SNP)
    sc_core::sc_signal<bool> TX_SNPFLITPEND_sig;
    sc_core::sc_signal<bool> TX_SNPFLITV_sig;
    sc_core::sc_signal<bool> TX_SNPLCRDV_sig;
    sc_core::sc_signal<RnIfxAdapter::snpflit_t> TX_SNPFLIT_sig;

    // TX channel signals (RSP)
    sc_core::sc_signal<bool> TX_RSPFLITPEND_sig;
    sc_core::sc_signal<bool> TX_RSPFLITV_sig;
    sc_core::sc_signal<bool> TX_RSPLCRDV_sig;
    sc_core::sc_signal<RnIfxAdapter::rspflit_t> TX_RSPFLIT_sig;

    // TX channel signals (DAT)
    sc_core::sc_signal<bool> TX_DATFLITPEND_sig;
    sc_core::sc_signal<bool> TX_DATFLITV_sig;
    sc_core::sc_signal<bool> TX_DATLCRDV_sig;
    sc_core::sc_signal<RnIfxAdapter::datflit_t> TX_DATFLIT_sig;

    // System signals
    sc_core::sc_signal<bool> TXSACTIVE_sig;
    sc_core::sc_signal<bool> RXSACTIVE_sig;
    sc_core::sc_signal<bool> SYSCOREQ_sig;
    sc_core::sc_signal<bool> SYSCOACK_sig;
};

#endif  // __RN_IFXADAPTER_TEST_HARNESS_H__
