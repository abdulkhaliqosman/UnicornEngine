#include "threadmanager.h"
#include <process.h>
#include "core/coreheader.h"

namespace unicore
{
    unsigned __stdcall ThreadFunc(void* pArguments)
    {
        ThreadBase* threadbase = static_cast<ThreadBase*>(pArguments);
        threadbase->Run();

        return 0;
    }

    void ThreadManager::Startup()
    {

    }

    void ThreadManager::Update()
    {

    }

    void ThreadManager::Shutdown()
    {

    }

    void ThreadManager::AddThread(ThreadBase* threadbase)
    {
        unsigned threadID;
        HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunc, threadbase, 0, &threadID);

        // TODO: init properly 
        threadbase->SetThreadId(threadID);
        threadbase->SetThreadHandle(hThread);
    }
}
