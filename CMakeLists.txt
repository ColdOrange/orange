cmake_minimum_required(VERSION 3.1)
project(orange)

option(ORANGE_ENABLE_TEST "enable testing for orange library" ON)

add_subdirectory(orange)

if (ORANGE_ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif()
