#include <memory>

#include <systemc>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <spdlog/spdlog.h>

#include <RnIfxAdapterTestHarness.h>


namespace
{

std::unique_ptr<RnIfxAdapterTestHarness> elaborated_design = std::make_unique<RnIfxAdapterTestHarness>();
constexpr auto dummy_address = 0xFF;
constexpr auto dummy_data_length = 255;
constexpr auto dummy_data_ptr = nullptr;

}  // namespace

using namespace ::testing;
using ::testing::_;

class RnIfxAdapterTests : public ::testing::Test {
protected:
    void SetUp() override
    {
        initiator = elaborated_design->get_initiator();
        rn_adapter = elaborated_design->get_rn_adapter();
        rn_adapter->enable_trace();
        rn_adapter->set_trace_time_unit(10, sc_core::SC_PS);

    }

    std::shared_ptr<SimpleInitiator> initiator;
    std::shared_ptr<RnIfxAdapter> rn_adapter;
};

TEST_F(RnIfxAdapterTests, RnIfxAdapterShouldSendCreditsToRnInitiator)
{
    // ASSERT_NE(initiator, nullptr);
    // EXPECT_CALL(*initiator, nb_transport_bw(_, _, _))
    //     .WillOnce(::testing::Return(tlm::TLM_ACCEPTED));

    sc_core::sc_start(0, sc_core::SC_NS);
    elaborated_design->rstb_intfrx_clk_sig.write(true);
    sc_core::sc_start(1600, sc_core::SC_PS);
    elaborated_design->rstb_intfrx_clk_sig.write(false);
    sc_core::sc_start(1600, sc_core::SC_PS);

    EXPECT_EQ(false, rn_adapter->TX_LINKACTIVEREQ_out.read());
    EXPECT_EQ(false, rn_adapter->TXSACTIVE_out.read());
    sc_core::sc_start(400, sc_core::SC_PS);

    elaborated_design->rstb_intfrx_clk_sig.write(true);
    sc_core::sc_start(2, sc_core::SC_NS);

    EXPECT_EQ(true, rn_adapter->TX_LINKACTIVEREQ_out.read());
    EXPECT_EQ(true, rn_adapter->TXSACTIVE_out.read());

    sc_core::sc_start(10, sc_core::SC_NS);
    EXPECT_EQ(true, rn_adapter->TX_LINKACTIVEREQ_out.read());
    EXPECT_EQ(true, rn_adapter->TXSACTIVE_out.read());

    rn_adapter->TX_LINKACTIVEACK_in.write(true);
    sc_core::sc_start(1, sc_core::SC_NS);

    rn_adapter->TX_REQLCRDV_in.write(true);
    rn_adapter->TX_RSPLCRDV_in.write(true);
    rn_adapter->TX_DATLCRDV_in.write(true);

    sc_core::sc_start(5, sc_core::SC_NS);

    rn_adapter->TX_REQLCRDV_in.write(false);
    rn_adapter->TX_RSPLCRDV_in.write(false);
    rn_adapter->TX_DATLCRDV_in.write(false);

    sc_core::sc_start(1, sc_core::SC_NS);
}
