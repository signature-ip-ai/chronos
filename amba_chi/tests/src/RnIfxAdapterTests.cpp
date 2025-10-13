#include <memory>

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <systemc>

#include <RnIfxAdapterTestHarness.h>


namespace
{

std::shared_ptr<RnIfxAdapterTestHarness> elaborated_design = std::make_shared<RnIfxAdapterTestHarness>();
constexpr auto dummy_address = 0xFF;
constexpr auto dummy_data_length = 255;
constexpr auto dummy_data_ptr = nullptr;

}  // namespace

class RnIfxAdapterTests : public ::testing::Test {
protected:
    void SetUp() override
    {
        initiator = elaborated_design->initiator;
        rnAdapter = elaborated_design->rnAdapter;
        sc_core::sc_start(0, sc_core::SC_NS);
    }

    std::shared_ptr<SimpleInitiator> initiator;
    std::shared_ptr<RnIfxAdapter> rnAdapter;
};

TEST_F(RnIfxAdapterTests, RnIfxAdapter_b_transport)
{
    tlm::tlm_generic_payload trans;
    trans.set_command(tlm::TLM_WRITE_COMMAND);
    trans.set_address(dummy_address);
    trans.set_data_ptr(dummy_data_ptr);
    trans.set_data_length(dummy_data_length);
    trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    sc_core::sc_time delay = sc_core::sc_time(10, sc_core::SC_NS);

    initiator->initiator_socket->b_transport(trans, delay);
    EXPECT_EQ(trans.get_response_status(), tlm::TLM_OK_RESPONSE);

    trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    tlm::tlm_phase phase(tlm::UNINITIALIZED_PHASE);
    initiator->initiator_socket->nb_transport_fw(trans, phase, delay);
    EXPECT_EQ(trans.get_response_status(), tlm::TLM_OK_RESPONSE);
}

TEST_F(RnIfxAdapterTests, RnIfxAdapter_nb_transport_fw)
{
    tlm::tlm_generic_payload trans;
    trans.set_command(tlm::TLM_WRITE_COMMAND);
    trans.set_address(dummy_address);
    trans.set_data_ptr(dummy_data_ptr);
    trans.set_data_length(dummy_data_length);
    trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    sc_core::sc_time delay = sc_core::sc_time(10, sc_core::SC_NS);

    tlm::tlm_phase phase(tlm::UNINITIALIZED_PHASE);
    initiator->initiator_socket->nb_transport_fw(trans, phase, delay);
    EXPECT_EQ(trans.get_response_status(), tlm::TLM_OK_RESPONSE);
}
