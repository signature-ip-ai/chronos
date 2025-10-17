#ifndef __RN_IFXADAPTER_TEST_HARNESS_H__
#define __RN_IFXADAPTER_TEST_HARNESS_H__

#include <memory>
#include <systemc>
#include <spdlog/spdlog.h>

#include <RnIfxAdapter.h>
#include <SimpleInitiator.h>
#include <flits/definitions.h>

struct RnIfxAdapterTestHarness
{
public:
    RnIfxAdapterTestHarness()
        : main_clock_sig("master_clk", 500, sc_core::SC_PS)
        , initiator(std::make_shared<SimpleInitiator>("SimpleInitiator"))
        , rn_adapter(std::make_shared<RnIfxAdapter>("RnIfxAdapter"))
    {
        bind_input_signals();
        initialize_unused_inputs();
        spdlog::info("Target Socket Name: {:s}", rn_adapter->target_socket.name());
        initiator->initiator_socket.bind(rn_adapter->target_socket);
    }

    void bind_input_signals()
    {
        rn_adapter->intfrx_clk_in(main_clock_sig);
        rn_adapter->rstb_intfrx_clk_in(rstb_intfrx_clk_sig);
    }

    void initialize_unused_inputs()
    {
        rn_adapter->RX_LINKACTIVEREQ_in.write(false);
        rn_adapter->TX_REQLCRDV_in.write(false);
        rn_adapter->TX_RSPLCRDV_in.write(false);
        rn_adapter->TX_DATLCRDV_in.write(false);
        rn_adapter->TX_LINKACTIVEACK_in.write(false);

        // RX channel inputs (from network)
        rn_adapter->RX_SNPFLITPEND_in.write(false);
        rn_adapter->RX_SNPFLITV_in.write(false);
        rn_adapter->RX_RSPFLITPEND_in.write(false);
        rn_adapter->RX_RSPFLITV_in.write(false);
        rn_adapter->RX_DATFLITPEND_in.write(false);
        rn_adapter->RX_DATFLITV_in.write(false);

        // System signals
        rn_adapter->RXSACTIVE_in.write(false);
        rn_adapter->SYSCOACK_in.write(false);

        // Initialize flit data to zero/default values
        rn_adapter->RX_SNPFLIT_in.write(flits::snpflit_t{});
        rn_adapter->RX_RSPFLIT_in.write(flits::rspflit_t{});
        rn_adapter->RX_DATFLIT_in.write(flits::datflit_t{});
    }

    std::shared_ptr<SimpleInitiator> get_initiator()
    {
        return this->initiator;
    }

    std::shared_ptr<RnIfxAdapter> get_rn_adapter()
    {
        return this->rn_adapter;
    }

    sc_core::sc_clock main_clock_sig;
    sc_core::sc_signal<bool> rstb_intfrx_clk_sig;

private:
    std::shared_ptr<SimpleInitiator> initiator;
    std::shared_ptr<RnIfxAdapter> rn_adapter;
};

#endif  // __RN_IFXADAPTER_TEST_HARNESS_H__
