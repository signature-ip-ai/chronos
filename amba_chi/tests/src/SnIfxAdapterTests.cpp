#include <memory>

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <systemc>

#include <SnIfxAdapterTestHarness.h>


static std::shared_ptr<SnIfxAdapterTestHarness> elaborated_design = std::make_shared<SnIfxAdapterTestHarness>();


class SnIfxAdapterTests : public ::testing::Test {
protected:
    void SetUp() override
    {
        target = elaborated_design->target;
        snAdapter = elaborated_design->snAdapter;
        sc_core::sc_start(0, sc_core::SC_NS);
    }

    std::shared_ptr<SimpleTarget> target;
    std::shared_ptr<SnIfxAdapter> snAdapter;
};

TEST_F(SnIfxAdapterTests, SnIfxAdapter_nb_transport_bw)
{
    tlm::tlm_generic_payload trans;
    trans.set_command(tlm::TLM_WRITE_COMMAND);
    trans.set_address(0xFF);
    trans.set_data_ptr(nullptr);
    trans.set_data_length(255);
    trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    sc_core::sc_time delay = sc_core::sc_time(10, sc_core::SC_NS);

    tlm::tlm_phase phase(tlm::UNINITIALIZED_PHASE);
    target->target_socket->nb_transport_bw(trans, phase, delay);
    EXPECT_EQ(trans.get_response_status(), tlm::TLM_OK_RESPONSE);
}
