//
// Created by wenjuxu on 2018/12/19.
//

#ifndef ORANGE_SCOPE_GUARD_H
#define ORANGE_SCOPE_GUARD_H

#include <exception>
#include <iostream>
#include <utility>
#include "common.h"
#include "noncopyable.h"

namespace orange
{

template<typename Func, bool OnSuccess = true, bool OnException = true>
class ScopeGuard : NonMovable
{
    static_assert(OnSuccess || OnException);

public:
    explicit ScopeGuard(Func&& func)
        : func_(std::forward<Func>(func)),
          canceled_(false),
          exceptions_(std::uncaught_exceptions())
    { }

    ~ScopeGuard() noexcept
    {
        try
        {
            if (!canceled_)
            {
                bool new_exception = exceptions_ < std::uncaught_exceptions();
                if ((OnSuccess && !new_exception) || (OnException && new_exception))
                {
                    func_();
                }
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "~ScopeGuard: exception while unwinding: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "~ScopeGuard: caught non-exception while unwinding" << std::endl;
        }
    }

    void Cancel() { canceled_ = true; }

private:
    Func func_;
    bool canceled_;
    int exceptions_;
};

template<typename Func>
class SuccessGuard : public ScopeGuard<Func, true, false>
{
public:
    explicit SuccessGuard(Func&& func)
        : ScopeGuard<Func, true, false>(std::forward<Func>(func))
    { }
};

template<typename Func>
class ExceptionGuard : public ScopeGuard<Func, false, true>
{
public:
    explicit ExceptionGuard(Func&& func)
        : ScopeGuard<Func, false, true>(std::forward<Func>(func))
    { }
};

#define DEFER(code) \
    auto UNIQUE_NAME(scope_guard) = orange::ScopeGuard([&] { do { code; } while (0); });

#define DEFER_ON_SUCCESS(code) \
    auto UNIQUE_NAME(success_guard) = orange::SuccessGuard([&] { do { code; } while (0); });

#define DEFER_ON_EXCEPTION(code) \
    auto UNIQUE_NAME(exception_guard) = orange::ExceptionGuard([&] { do { code; } while (0); });

} // namespace orange

#endif // ORANGE_SCOPE_GUARD_H
