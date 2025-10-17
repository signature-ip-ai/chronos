cmake_minimum_required(VERSION 3.20)

project(ambachicast)

find_package(SystemCLanguage REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CUSTOM_CXX_FLAGS -Wall -Werror -Wno-format -O0 -g)

########## Build Library
get_target_property(SYSTEMC_INCLUDE_DIRS SystemC::systemc INTERFACE_INCLUDE_DIRECTORIES)

file(GLOB_RECURSE sources src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC include ${SYSTEMC_INCLUDE_DIRS} ${SPDLOG_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${CUSTOM_CXX_FLAGS})
target_link_libraries(${PROJECT_NAME} PUBLIC SystemC::systemc)

########## Install Package Library
file(GLOB_RECURSE TARGET_LIBRARY_HEADERS
    include/RnIfxAdapter.h
    include/SnIfxAdapter.h
    include/ProgIfxAdapter.h
    include/QpIfxAdapter.h
    include/ClkResetIfx.h
    include/chi_tlm/chi_enums.h
    include/chi_tlm/chi_tlm_extension.h
    include/chi_tlm/chi_credit_extension.h
    include/chi_tlm/chi_packet.h
    include/flits/definitions.h)

target_sources(${PROJECT_NAME} PUBLIC FILE_SET HEADERS BASE_DIRS include FILES ${TARGET_LIBRARY_HEADERS})
install(TARGETS ${PROJECT_NAME} FILE_SET HEADERS)

########## Tests
enable_testing()

########## RnIfxAdapterTests Executable
file(GLOB RNIFXADAPTER_TESTS_SOURCES tests/src/RnIfxAdapterTests.cpp tests/src/ambachicast_tests.cpp)

add_executable(RnIfxAdapterTests ${RNIFXADAPTER_TESTS_SOURCES})

get_target_property(SYSTEMC_INCLUDE_DIRS SystemC::systemc INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(SPDLOG_INCLUDE_DIRS spdlog::spdlog INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(GTEST_INCLUDE_DIRS GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(RnIfxAdapterTests PUBLIC
    include
    tests/include
    ${SYSTEMC_INCLUDE_DIRS}
    ${SPDLOG_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS})

target_compile_options(RnIfxAdapterTests PRIVATE ${CUSTOM_CXX_FLAGS})
target_link_libraries(RnIfxAdapterTests SystemC::systemc gtest::gtest spdlog::spdlog ${PROJECT_NAME})

########## SnIfxAdapterTests Executable
file(GLOB SNIFXADAPTER_TESTS_SOURCES tests/src/SnIfxAdapterTests.cpp tests/src/ambachicast_tests.cpp)

add_executable(SnIfxAdapterTests ${SNIFXADAPTER_TESTS_SOURCES})

get_target_property(SYSTEMC_INCLUDE_DIRS SystemC::systemc INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(SPDLOG_INCLUDE_DIRS spdlog::spdlog INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(GTEST_INCLUDE_DIRS GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(SnIfxAdapterTests PUBLIC
    include
    tests/include
    ${SYSTEMC_INCLUDE_DIRS}
    ${SPDLOG_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS})

target_compile_options(SnIfxAdapterTests PRIVATE ${CUSTOM_CXX_FLAGS})
target_link_libraries(SnIfxAdapterTests SystemC::systemc gtest::gtest spdlog::spdlog ${PROJECT_NAME})

########## FlitTests Executable
file(GLOB FLIT_TESTS_SOURCES
    tests/src/flittests/ChiRspFlitTests.cpp
    tests/src/flittests/ChiReqFlitTests.cpp
    tests/src/flittests/ChiDatFlitTests.cpp
    tests/src/flittests/ChiSnpFlitTests.cpp
    tests/src/ambachicast_tests.cpp)

add_executable(FlitTests ${FLIT_TESTS_SOURCES})

get_target_property(SYSTEMC_INCLUDE_DIRS SystemC::systemc INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(SPDLOG_INCLUDE_DIRS spdlog::spdlog INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(GTEST_INCLUDE_DIRS GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(FlitTests PUBLIC
    include
    tests/include
    ${SYSTEMC_INCLUDE_DIRS}
    ${SPDLOG_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS})

target_compile_options(FlitTests PRIVATE ${CUSTOM_CXX_FLAGS})
target_link_libraries(FlitTests SystemC::systemc gtest::gtest spdlog::spdlog ${PROJECT_NAME})
