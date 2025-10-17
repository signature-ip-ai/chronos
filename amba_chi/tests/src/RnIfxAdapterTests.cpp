#include <memory>

#include <systemc>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <spdlog/spdlog.h>

#include <RnIfxAdapterTestHarness.h>

#include <chi_tlm/chi_tlm_extension.h>
#include <chi_tlm/chi_credit_extension.h>
#include <chi_tlm/chi_enums.h>

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
    }

    std::shared_ptr<SimpleInitiator> initiator;
    std::shared_ptr<RnIfxAdapter> rn_adapter;
};

TEST_F(RnIfxAdapterTests, RnIfxAdapterShouldSendCreditsToRnInitiator)
{
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

TEST_F(RnIfxAdapterTests, RnIfxAdapterShouldHandleChiReqMessage)
{
    chi::ChiExtension* chi_message = new chi::ChiExtension;
    chi_message->channel = chi::ChiChannel::REQ;

    tlm::tlm_generic_payload trans;
    trans.set_extension(chi_message);

    tlm::tlm_phase phase = chi::REQ;
    sc_core::sc_time time = sc_core::SC_ZERO_TIME;
    tlm::tlm_sync_enum response = initiator->initiator_socket->nb_transport_fw(trans, phase, time);

    EXPECT_EQ(response, tlm::TLM_ACCEPTED);
    EXPECT_EQ(trans.get_response_status(), tlm::TLM_OK_RESPONSE);
}

TEST_F(RnIfxAdapterTests, RnIfxAdapterShouldHandleChiWdatMessage)
{
    chi::ChiExtension* chi_message = new chi::ChiExtension;
    chi_message->channel = chi::ChiChannel::WDAT;

    tlm::tlm_generic_payload trans;
    trans.set_extension(chi_message);

    tlm::tlm_phase phase = chi::WDAT;
    sc_core::sc_time time = sc_core::SC_ZERO_TIME;
    tlm::tlm_sync_enum response = initiator->initiator_socket->nb_transport_fw(trans, phase, time);

    EXPECT_EQ(response, tlm::TLM_ACCEPTED);
    EXPECT_EQ(trans.get_response_status(), tlm::TLM_OK_RESPONSE);
}

TEST_F(RnIfxAdapterTests, RnIfxAdapterShouldHandleChiSrspMessage)
{
    chi::ChiExtension* chi_message = new chi::ChiExtension;
    chi_message->channel = chi::ChiChannel::SRSP;

    tlm::tlm_generic_payload trans;
    trans.set_extension(chi_message);

    tlm::tlm_phase phase = chi::SRSP;
    sc_core::sc_time time = sc_core::SC_ZERO_TIME;
    tlm::tlm_sync_enum response = initiator->initiator_socket->nb_transport_fw(trans, phase, time);

    EXPECT_EQ(response, tlm::TLM_ACCEPTED);
    EXPECT_EQ(trans.get_response_status(), tlm::TLM_OK_RESPONSE);
}

TEST_F(RnIfxAdapterTests, RnIfxAdapterShouldNotHandleChiSnpMessage)
{
    chi::ChiExtension* chi_message = new chi::ChiExtension;
    chi_message->channel = chi::ChiChannel::SNP;

    tlm::tlm_generic_payload trans;
    trans.set_extension(chi_message);

    tlm::tlm_phase phase = chi::SNP;
    sc_core::sc_time time = sc_core::SC_ZERO_TIME;
    tlm::tlm_sync_enum response = initiator->initiator_socket->nb_transport_fw(trans, phase, time);

    EXPECT_EQ(response, tlm::TLM_ACCEPTED);
    EXPECT_EQ(trans.get_response_status(), tlm::TLM_COMMAND_ERROR_RESPONSE);
}

TEST_F(RnIfxAdapterTests, RnIfxAdapterShouldNotHandleChiRdatMessage)
{
    chi::ChiExtension* chi_message = new chi::ChiExtension;
    chi_message->channel = chi::ChiChannel::RDAT;

    tlm::tlm_generic_payload trans;
    trans.set_extension(chi_message);

    tlm::tlm_phase phase = chi::RDAT;
    sc_core::sc_time time = sc_core::SC_ZERO_TIME;
    tlm::tlm_sync_enum response = initiator->initiator_socket->nb_transport_fw(trans, phase, time);

    EXPECT_EQ(response, tlm::TLM_ACCEPTED);
    EXPECT_EQ(trans.get_response_status(), tlm::TLM_COMMAND_ERROR_RESPONSE);
}

TEST_F(RnIfxAdapterTests, RnIfxAdapterShouldNotHandleChiCrspMessage)
{
    chi::ChiExtension* chi_message = new chi::ChiExtension;
    chi_message->channel = chi::ChiChannel::CRSP;

    tlm::tlm_generic_payload trans;
    trans.set_extension(chi_message);

    tlm::tlm_phase phase = chi::CRSP;
    sc_core::sc_time time = sc_core::SC_ZERO_TIME;
    tlm::tlm_sync_enum response = initiator->initiator_socket->nb_transport_fw(trans, phase, time);

    EXPECT_EQ(response, tlm::TLM_ACCEPTED);
    EXPECT_EQ(trans.get_response_status(), tlm::TLM_COMMAND_ERROR_RESPONSE);
}
