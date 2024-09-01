#pragma once

#include <cstdio>

namespace Unicorn
{
    enum class LogLevels
    {
        All,
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
        Off
    };

    template<typename ... Args>
    void LogConsole(LogLevels level, const char* const fmt, Args&&... args)
    {
        static constexpr LogLevels MinLogLevel = LogLevels::All;
        if (level >= level)
        {
            printf(fmt, std::forward<Args...>(args...));
        }
    }
}

#define ucLogMessage(level, ...) Unicorn::LogConsole(level, __VA_ARGS__);
#define ucLogTrace(...)          Unicorn::LogConsole(Unicorn::LogLevels::Trace, __VA_ARGS__);
#define ucLogDebug(...)          Unicorn::LogConsole(Unicorn::LogLevels::Debug, __VA_ARGS__);
#define ucLogInfo(...)           Unicorn::LogConsole(Unicorn::LogLevels::Info, __VA_ARGS__);
#define ucLogWarning(...)        Unicorn::LogConsole(Unicorn::LogLevels::Warning, __VA_ARGS__);
#define ucLogError(...)          Unicorn::LogConsole(Unicorn::LogLevels::Error, __VA_ARGS__);
#define ucLogFatal(...)          Unicorn::LogConsole(Unicorn::LogLevels::Fatal, __VA_ARGS__);
