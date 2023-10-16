#pragma once

#include "Windows.h"

namespace unicore
{
    class ThreadBase
    {
    public:
        inline virtual ~ThreadBase() {}

        virtual void Init() = 0;
        virtual void Run() = 0;

        inline void SetThreadId(unsigned id) { m_ThreadId = id; }
        inline unsigned GetThreadId() const { return m_ThreadId; }

        inline HANDLE GetThreadHandle() const { return m_ThreadHandle; }
        inline void SetThreadHandle(HANDLE handle) { m_ThreadHandle = handle; }

    private:
        unsigned m_ThreadId = 0;
        HANDLE m_ThreadHandle;
    };
}
