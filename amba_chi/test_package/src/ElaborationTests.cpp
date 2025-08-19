#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <systemc>

#include <RnIfxAdapter.hpp>
#include <SnIfxAdapter.hpp>

TEST(ElaborationTests, ElaborateRnIfxAdapter)
{
    RnIfxAdapter rnAdapter("RnIfxAdapter0");
    spdlog::info("Target Socket Name: {:s}", rnAdapter.target_socket.name());
}

TEST(ElaborationTests, ElaborateSnIfxAdapter)
{
    SnIfxAdapter snAdapter("SnIfxAdapter0");
    spdlog::info("Initiator Socket Name: {:s}", snAdapter.initiator_socket.name());
}
