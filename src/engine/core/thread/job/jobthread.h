#pragma once

#include "core/thread/base/threadbase.h"

namespace Unicorn
{
    class JobBase;
    class JobThread : public ThreadBase
    {
    public:
        void Run() override;
        bool AddJob(JobBase* job);
    private:
        void NotifyJobFinished();

        JobBase* m_CurrentJob;
        JobBase* m_NextJob;
    };
}