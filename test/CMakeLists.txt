set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${PROJECT_SOURCE_DIR}/cmake/orange_define_tests.cmake)

orange_define_tests(
    TEST scope_guard_test SOURCES scope_guard_test.cpp
)
