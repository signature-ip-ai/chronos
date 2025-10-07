cmake_minimum_required(VERSION 3.20)

project(ambachicast_tests CXX)

find_package(SystemCLanguage CONFIG REQUIRED)
find_package(ambachicast CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CUSTOM_CXX_FLAGS -Wall -Werror -Wno-format -O0 -g)

########## RnIfxAdapterTests Executable
file(GLOB RNIFXADAPTER_TESTS_SOURCES src/RnIfxAdapterTests.cpp src/ambachicast_tests.cpp)

add_executable(RnIfxAdapterTests ${RNIFXADAPTER_TESTS_SOURCES})

get_target_property(SYSTEMC_INCLUDE_DIRS SystemC::systemc INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(SPDLOG_INCLUDE_DIRS spdlog::spdlog INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(GTEST_INCLUDE_DIRS GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(AMBACHICAST_INCLUDE_DIRS ambachicast::ambachicast INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(RnIfxAdapterTests PUBLIC
    include
    ${SYSTEMC_INCLUDE_DIRS}
    ${SPDLOG_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
    ${AMBACHICAST_INCLUDE_DIRS})

target_compile_options(RnIfxAdapterTests PRIVATE ${CUSTOM_CXX_FLAGS})
target_link_libraries(RnIfxAdapterTests SystemC::systemc spdlog::spdlog ambachicast::ambachicast gtest::gtest)

########## SnIfxAdapterTests Executable
file(GLOB SNIFXADAPTER_TESTS_SOURCES src/SnIfxAdapterTests.cpp src/ambachicast_tests.cpp)

add_executable(SnIfxAdapterTests ${SNIFXADAPTER_TESTS_SOURCES})

get_target_property(SYSTEMC_INCLUDE_DIRS SystemC::systemc INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(SPDLOG_INCLUDE_DIRS spdlog::spdlog INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(GTEST_INCLUDE_DIRS GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(AMBACHICAST_INCLUDE_DIRS ambachicast::ambachicast INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(SnIfxAdapterTests PUBLIC
    include
    ${SYSTEMC_INCLUDE_DIRS}
    ${SPDLOG_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
    ${AMBACHICAST_INCLUDE_DIRS})

target_compile_options(SnIfxAdapterTests PRIVATE ${CUSTOM_CXX_FLAGS})
target_link_libraries(SnIfxAdapterTests SystemC::systemc spdlog::spdlog ambachicast::ambachicast gtest::gtest)
