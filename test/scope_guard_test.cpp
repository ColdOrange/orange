//
// Created by wenjuxu on 2018/12/19.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "scope_guard.h"

TEST_CASE("Test scope guard", "[scope_guard]")
{
    int x;

    try
    {
        x = -1;
        auto scope_guard = orange::ScopeGuard([&] { x = 42; });
        throw std::runtime_error("");
    }
    catch (...)
    {
        REQUIRE(x == 42);
    }
}

TEST_CASE("Test cancel scope guard", "[scope_guard]")
{
    int x;
    {
        x = -1;
        auto scope_guard = orange::ScopeGuard([&] { x = 42; });
        scope_guard.Cancel();
    }
    REQUIRE(x == -1);
}

TEST_CASE("Test defer", "[defer]")
{
    int x;

    try
    {
        x = -1;
        DEFER(x = 42);
        throw std::runtime_error("");
    }
    catch (...)
    {
        REQUIRE(x == 42);
    }
}

TEST_CASE("Test success guard", "[success_guard]")
{
    int x;

    SECTION("On success")
    {
        {
            x = -1;
            auto success_guard = orange::SuccessGuard([&] { x = 42; });
        }
        REQUIRE(x == 42);
    }

    SECTION("On exception")
    {
        try
        {
            x = -1;
            auto success_guard = orange::SuccessGuard([&] { x = 42; });
            throw std::runtime_error("");
        }
        catch (...)
        {
            REQUIRE(x == -1);
        }
    }
}

TEST_CASE("Test defer on success", "[defer_on_success]")
{
    int x;

    SECTION("On success")
    {
        {
            x = -1;
            DEFER_ON_SUCCESS(x = 42);
        }
        REQUIRE(x == 42);
    }

    SECTION("On exception")
    {
        try
        {
            x = -1;
            DEFER_ON_SUCCESS(x = 42);
            throw std::runtime_error("");
        }
        catch (...)
        {
            REQUIRE(x == -1);
        }
    }
}

TEST_CASE("Test exception guard", "[exception_guard]")
{
    int x;

    SECTION("On success")
    {
        {
            x = -1;
            auto exception_guard = orange::ExceptionGuard([&] { x = 42; });
        }
        REQUIRE(x == -1);
    }

    SECTION("On exception")
    {
        try
        {
            x = -1;
            auto exception_guard = orange::ExceptionGuard([&] { x = 42; });
            throw std::runtime_error("");
        }
        catch (...)
        {
            REQUIRE(x == 42);
        }
    }
}

TEST_CASE("Test defer on exception", "[defer_on_exception]")
{
    int x;

    SECTION("On success")
    {
        {
            x = -1;
            DEFER_ON_EXCEPTION(x = 42);
        }
        REQUIRE(x == -1);
    }

    SECTION("On exception")
    {
        try
        {
            x = -1;
            DEFER_ON_EXCEPTION(x = 42);
            throw std::runtime_error("");
        }
        catch (...)
        {
            REQUIRE(x == 42);
        }
    }
}
