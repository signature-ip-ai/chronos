cmake_minimum_required(VERSION 3.20)

project(chica2tlm)

find_package(SystemCLanguage REQUIRED)
find_package(spdlog REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CUSTOM_CXX_FLAGS -Wall -Werror -Wno-format)

########## Build Library
get_target_property(SYSTEMC_INCLUDE_DIRS SystemC::systemc INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(SPDLOG_INCLUDE_DIRS spdlog::spdlog INTERFACE_INCLUDE_DIRECTORIES)

file(GLOB sources src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC include ${SYSTEMC_INCLUDE_DIRS} ${SPDLOG_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${CUSTOM_CXX_FLAGS})
target_link_libraries(${PROJECT_NAME} SystemC::systemc spdlog::spdlog)


########## Install Package Library
file(GLOB_RECURSE TARGET_LIBRARY_HEADERS include/ca2tlm.hpp)
target_sources(${PROJECT_NAME} PUBLIC FILE_SET HEADERS BASE_DIRS include FILES ${TARGET_LIBRARY_HEADERS})
install(TARGETS ${PROJECT_NAME} FILE_SET HEADERS)
