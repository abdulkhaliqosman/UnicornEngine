#include "core/coreheader.h"

namespace unicore
{
    class JobBase;
    class JobThread;

    class JobManager
    {
    public:
        void AddJob(JobBase* job);

        void Startup();
        void Update();
        void Shutdown();

    private:
        List<JobThread*> m_Threads;
        List<JobBase*> m_Jobs;
    };
}
