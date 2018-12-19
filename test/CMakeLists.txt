set(CMAKE_CXX_STANDARD 17)

include(${PROJECT_SOURCE_DIR}/cmake/orange_define_tests.cmake)

orange_define_tests(
    TEST scope_guard_test SOURCES scope_guard_test.cpp
)
