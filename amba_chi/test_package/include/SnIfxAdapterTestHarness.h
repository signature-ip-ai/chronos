#ifndef __SN_IFXADAPTER_TEST_HARNESS_H__
#define __SN_IFXADAPTER_TEST_HARNESS_H__

#include <memory>
#include <systemc>

#include <SnIfxAdapter.h>
#include <SimpleTarget.h>


struct SnIfxAdapterTestHarness
{
    SnIfxAdapterTestHarness()
        : target(std::make_shared<SimpleTarget>("SimpleTarget"))
        , snAdapter(std::make_shared<SnIfxAdapter>("SnIfxAdapter"))
    {
        bind_all_ports();
        initialize_unused_inputs();
        spdlog::info("Initiator Socket Name: {:s}", snAdapter->initiator_socket.name());
        snAdapter->initiator_socket.bind(target->target_socket);
    }

    void bind_all_ports()
    {
        // Interface clocks (outputs from snAdapter)
        snAdapter->intfrx_clk(intfrx_clk_sig);
        snAdapter->rstb_intfrx_clk(rstb_intfrx_clk_sig);

        // Link activation
        snAdapter->TX_LINKACTIVEREQ(TX_LINKACTIVEREQ_sig);
        snAdapter->TX_LINKACTIVEACK(TX_LINKACTIVEACK_sig);
        snAdapter->RX_LINKACTIVEREQ(RX_LINKACTIVEREQ_sig);
        snAdapter->RX_LINKACTIVEACK(RX_LINKACTIVEACK_sig);

        // RX channels (RSP)
        snAdapter->RX_RSPFLITPEND(RX_RSPFLITPEND_sig);
        snAdapter->RX_RSPFLITV(RX_RSPFLITV_sig);
        snAdapter->RX_RSPLCRDV(RX_RSPLCRDV_sig);
        snAdapter->RX_RSPFLIT(RX_RSPFLIT_sig);

        // RX channels (DAT)
        snAdapter->RX_DATFLITPEND(RX_DATFLITPEND_sig);
        snAdapter->RX_DATFLITV(RX_DATFLITV_sig);
        snAdapter->RX_DATLCRDV(RX_DATLCRDV_sig);
        snAdapter->RX_DATFLIT(RX_DATFLIT_sig);

        // TX channels (REQ)
        snAdapter->TX_REQFLITPEND(TX_REQFLITPEND_sig);
        snAdapter->TX_REQFLITV(TX_REQFLITV_sig);
        snAdapter->TX_REQLCRDV(TX_REQLCRDV_sig);
        snAdapter->TX_REQFLIT(TX_REQFLIT_sig);

        // TX channels (DAT)
        snAdapter->TX_DATFLITPEND(TX_DATFLITPEND_sig);
        snAdapter->TX_DATFLITV(TX_DATFLITV_sig);
        snAdapter->TX_DATLCRDV(TX_DATLCRDV_sig);
        snAdapter->TX_DATFLIT(TX_DATFLIT_sig);

        // System signals
        snAdapter->TXSACTIVE(TXSACTIVE_sig);
        snAdapter->RXSACTIVE(RXSACTIVE_sig);
    }

    void initialize_unused_inputs()
    {
        // Link activation inputs
        TX_LINKACTIVEREQ_sig.write(false);
        RX_LINKACTIVEACK_sig.write(false);

        // Credit inputs - initialize to true (credits available)
        RX_RSPLCRDV_sig.write(true);
        RX_DATLCRDV_sig.write(true);

        // TX channel inputs (from slave device)
        TX_REQFLITPEND_sig.write(false);
        TX_REQFLITV_sig.write(false);
        TX_DATFLITPEND_sig.write(false);
        TX_DATFLITV_sig.write(false);

        // System signal
        TXSACTIVE_sig.write(false);

        // Initialize flit data to zero/default values
        TX_REQFLIT_sig.write(SnIfxAdapter::reqflit_t{});
        TX_DATFLIT_sig.write(SnIfxAdapter::datflit_t{});
    }

    std::shared_ptr<SimpleTarget> target;
    std::shared_ptr<SnIfxAdapter> snAdapter;

    // Interface clock signals (outputs from snAdapter)
    sc_core::sc_signal<bool> intfrx_clk_sig;
    sc_core::sc_signal<bool> rstb_intfrx_clk_sig;

    // Link activation signals
    sc_core::sc_signal<bool> TX_LINKACTIVEREQ_sig;
    sc_core::sc_signal<bool> TX_LINKACTIVEACK_sig;
    sc_core::sc_signal<bool> RX_LINKACTIVEREQ_sig;
    sc_core::sc_signal<bool> RX_LINKACTIVEACK_sig;

    // RX channel signals (RSP - from network to slave)
    sc_core::sc_signal<bool> RX_RSPFLITPEND_sig;
    sc_core::sc_signal<bool> RX_RSPFLITV_sig;
    sc_core::sc_signal<bool> RX_RSPLCRDV_sig;
    sc_core::sc_signal<SnIfxAdapter::rspflit_t> RX_RSPFLIT_sig;

    // RX channel signals (DAT - from network to slave)
    sc_core::sc_signal<bool> RX_DATFLITPEND_sig;
    sc_core::sc_signal<bool> RX_DATFLITV_sig;
    sc_core::sc_signal<bool> RX_DATLCRDV_sig;
    sc_core::sc_signal<SnIfxAdapter::datflit_t> RX_DATFLIT_sig;

    // TX channel signals (REQ - from slave to network)
    sc_core::sc_signal<bool> TX_REQFLITPEND_sig;
    sc_core::sc_signal<bool> TX_REQFLITV_sig;
    sc_core::sc_signal<bool> TX_REQLCRDV_sig;
    sc_core::sc_signal<SnIfxAdapter::reqflit_t> TX_REQFLIT_sig;

    // TX channel signals (DAT - from slave to network)
    sc_core::sc_signal<bool> TX_DATFLITPEND_sig;
    sc_core::sc_signal<bool> TX_DATFLITV_sig;
    sc_core::sc_signal<bool> TX_DATLCRDV_sig;
    sc_core::sc_signal<SnIfxAdapter::datflit_t> TX_DATFLIT_sig;

    // System signals
    sc_core::sc_signal<bool> TXSACTIVE_sig;
    sc_core::sc_signal<bool> RXSACTIVE_sig;
};

#endif  // __SN_IFXADAPTER_TEST_HARNESS_H__
