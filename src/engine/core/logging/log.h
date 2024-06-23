#pragma once

namespace unicore
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
}

#define ucLog 
#define ucTrace
#define ucDebug
#define ucInfo
#define ucWarning
#define ucError
#define ucFatal
