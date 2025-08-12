#include <gtest/gtest.h>

#include <RnIfxAdapter.hpp>
#include <SnIfxAdapter.hpp>

int main(int argc, char* argv[])
{
    RnIfxAdapter rnAdapter("RnIfxAdapter");
    SnIfxAdapter snAdapter("SnIfxAdapter");

    testing::InitGoogleTest(&argc, argv);
    int status = RUN_ALL_TESTS();
    return status;
}
