set(CMAKE_CXX_STANDARD 17)

set(ORANGE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/orange)
set(CATCH2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third_party/Catch2/single_include/catch2)

set(TEST_SOURCES
        scope_guard_test.cpp
        main.cpp)

add_executable(orange_test ${TEST_SOURCES})
target_include_directories(orange_test PRIVATE ${CATCH2_INCLUDE_DIR} ${ORANGE_INCLUDE_DIR})

add_test(NAME orange_test COMMAND orange_test -o report.xml -r junit)
