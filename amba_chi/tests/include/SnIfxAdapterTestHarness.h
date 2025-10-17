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
        bind_input_signals();
        initialize_unused_inputs();
        spdlog::info("Initiator Socket Name: {:s}", snAdapter->initiator_socket.name());
        snAdapter->initiator_socket.bind(target->target_socket);
    }

    void bind_input_signals()
    {
        snAdapter->intfrx_clk_in(intfrx_clk_sig);
        snAdapter->rstb_intfrx_clk_in(rstb_intfrx_clk_sig);
    }

    void initialize_unused_inputs()
    {
        // Link activation inputs
        snAdapter->RX_LINKACTIVEREQ_in.write(false);
        snAdapter->TX_LINKACTIVEACK_in.write(false);

        // Credit inputs - initialize to false
        snAdapter->TX_RSPLCRDV_in.write(false);
        snAdapter->TX_DATLCRDV_in.write(false);

        // RX channel inputs (from slave device)
        snAdapter->RX_REQFLITPEND_in.write(false);
        snAdapter->RX_REQFLITV_in.write(false);
        snAdapter->RX_DATFLITPEND_in.write(false);
        snAdapter->RX_DATFLITV_in.write(false);

        // System signal
        snAdapter->RXSACTIVE_in.write(false);

        // Initialize flit data to zero/default values
        snAdapter->RX_REQFLIT_in.write(SnIfxAdapter::reqflit_t{});
        snAdapter->RX_DATFLIT_in.write(SnIfxAdapter::datflit_t{});
    }

    std::shared_ptr<SimpleTarget> target;
    std::shared_ptr<SnIfxAdapter> snAdapter;

    sc_core::sc_signal<bool> intfrx_clk_sig;
    sc_core::sc_signal<bool> rstb_intfrx_clk_sig;
};

#endif  // __SN_IFXADAPTER_TEST_HARNESS_H__
