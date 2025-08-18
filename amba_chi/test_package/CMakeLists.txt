cmake_minimum_required(VERSION 3.20)

project(ambachicast_tests CXX)

find_package(SystemCLanguage CONFIG REQUIRED)
find_package(ambachicast CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CUSTOM_CXX_FLAGS -Wall -Werror -Wno-format)

########## Main Executable
file(GLOB AMBACHICAST_TESTS_SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${AMBACHICAST_TESTS_SOURCES})

get_target_property(SYSTEMC_INCLUDE_DIRS SystemC::systemc INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(SPDLOG_INCLUDE_DIRS spdlog::spdlog INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(GTEST_INCLUDE_DIRS GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(AMBACHICAST_INCLUDE_DIRS ambachicast::ambachicast INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
    ${SYSTEMC_INCLUDE_DIRS}
    ${SPDLOG_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
    ${AMBACHICAST_INCLUDE_DIRS})

target_compile_options(${PROJECT_NAME} PRIVATE ${CUSTOM_CXX_FLAGS})

target_link_libraries(${PROJECT_NAME}
    SystemC::systemc
    spdlog::spdlog
    ambachicast::ambachicast
    gtest::gtest)
