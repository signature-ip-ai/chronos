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
        initialize_unused_inputs();
        spdlog::info("Target Socket Name: {:s}", rnAdapter->target_socket.name());
        initiator->initiator_socket.bind(rnAdapter->target_socket);
    }

    void initialize_unused_inputs()
    {
        rnAdapter->TX_LINKACTIVEREQ_in.write(false);
        rnAdapter->RX_REQLCRDV_in.write(true);
        rnAdapter->RX_RSPLCRDV_in.write(true);
        rnAdapter->RX_DATLCRDV_in.write(true);
        rnAdapter->RX_LINKACTIVEACK_in.write(false);

        // TX channel inputs (from network)
        rnAdapter->TX_SNPFLITPEND_in.write(false);
        rnAdapter->TX_SNPFLITV_in.write(false);
        rnAdapter->TX_RSPFLITPEND_in.write(false);
        rnAdapter->TX_RSPFLITV_in.write(false);
        rnAdapter->TX_DATFLITPEND_in.write(false);
        rnAdapter->TX_DATFLITV_in.write(false);

        // System signals
        rnAdapter->TXSACTIVE_in.write(false);
        rnAdapter->SYSCOACK_in.write(false);

        // Initialize flit data to zero/default values
        rnAdapter->TX_SNPFLIT_in.write(RnIfxAdapter::snpflit_t{});
        rnAdapter->TX_RSPFLIT_in.write(RnIfxAdapter::rspflit_t{});
        rnAdapter->TX_DATFLIT_in.write(RnIfxAdapter::datflit_t{});
    }

    std::shared_ptr<SimpleInitiator> initiator;
    std::shared_ptr<RnIfxAdapter> rnAdapter;
};

#endif  // __RN_IFXADAPTER_TEST_HARNESS_H__
