cmake_minimum_required(VERSION 2.8)

project(jtl CXX)

option(JTL_ENABLE_TESTS "Enable test targets for JTL" OFF)

add_library(jtl INTERFACE)
target_include_directories(jtl INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include/)

if(JTL_ENABLE_TESTS)
    add_subdirectory(tests)
endif()
