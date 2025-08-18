#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <systemc>

#include <RnIfxAdapter.hpp>
#include <SnIfxAdapter.hpp>

TEST(ElaborationTests, ElaborateRnIfxAdapter)
{
    RnIfxAdapter rnAdapter("RnIfxAdapter0");
}

TEST(ElaborationTests, ElaborateSnIfxAdapter)
{
    SnIfxAdapter rnAdapter("SnIfxAdapter0");
}
