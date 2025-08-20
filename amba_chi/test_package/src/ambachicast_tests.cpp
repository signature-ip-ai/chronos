#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

int main(int argc, char* argv[])
{
    spdlog::set_pattern("%^[%9l ]%$ %v");
    testing::InitGoogleTest(&argc, argv);
    int status = RUN_ALL_TESTS();
    return status;
}
