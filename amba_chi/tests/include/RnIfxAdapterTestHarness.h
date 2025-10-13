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
        bind_input_signals();
        initialize_unused_inputs();
        spdlog::info("Target Socket Name: {:s}", rnAdapter->target_socket.name());
        initiator->initiator_socket.bind(rnAdapter->target_socket);
    }

    void bind_input_signals()
    {
        rnAdapter->intfrx_clk_in(intfrx_clk_sig);
        rnAdapter->rstb_intfrx_clk_in(rstb_intfrx_clk_sig);
    }

    void initialize_unused_inputs()
    {
        rnAdapter->RX_LINKACTIVEREQ_in.write(false);
        rnAdapter->TX_REQLCRDV_in.write(false);
        rnAdapter->TX_RSPLCRDV_in.write(false);
        rnAdapter->TX_DATLCRDV_in.write(false);
        rnAdapter->TX_LINKACTIVEACK_in.write(false);

        // RX channel inputs (from network)
        rnAdapter->RX_SNPFLITPEND_in.write(false);
        rnAdapter->RX_SNPFLITV_in.write(false);
        rnAdapter->RX_RSPFLITPEND_in.write(false);
        rnAdapter->RX_RSPFLITV_in.write(false);
        rnAdapter->RX_DATFLITPEND_in.write(false);
        rnAdapter->RX_DATFLITV_in.write(false);

        // System signals
        rnAdapter->RXSACTIVE_in.write(false);
        rnAdapter->SYSCOACK_in.write(false);

        // Initialize flit data to zero/default values
        rnAdapter->RX_SNPFLIT_in.write(RnIfxAdapter::snpflit_t{});
        rnAdapter->RX_RSPFLIT_in.write(RnIfxAdapter::rspflit_t{});
        rnAdapter->RX_DATFLIT_in.write(RnIfxAdapter::datflit_t{});
    }

    std::shared_ptr<SimpleInitiator> initiator;
    std::shared_ptr<RnIfxAdapter> rnAdapter;

    sc_core::sc_signal<bool> intfrx_clk_sig;
    sc_core::sc_signal<bool> rstb_intfrx_clk_sig;
};

#endif  // __RN_IFXADAPTER_TEST_HARNESS_H__
