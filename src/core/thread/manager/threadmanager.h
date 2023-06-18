#pragma once

#include "core/container/list.h"

namespace unicore
{
    class JobThread;
    class ThreadBase;

    class ThreadManager
    {
    public:
        inline void SetThreadNum(int num) { m_ThreadNum = num; }
        void AddThread(ThreadBase* threadbase);

        void Startup();
        void Update();
        void Shutdown();

    private:

        int m_ThreadNum = 2;

        List<ThreadBase*> m_ThreadList;
    };
}
