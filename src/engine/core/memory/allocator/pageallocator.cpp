#include "pageallocator.h"
#include <Windows.h>

namespace unicore
{
    void PageAllocator::Startup()
    {
        //TODO: make system info available somewhere else on the platform level

        SYSTEM_INFO sysinfo;
        GetSystemInfo(&sysinfo);
        m_PageSize = sysinfo.dwPageSize;
        // allocate 1 page size for our memory management usage 
    }

    void PageAllocator::Update()
    {

    }

    void PageAllocator::Shutdown()
    {

    }

    void* Allocate(uint64_t size)
    {

    }

    void Deallocate()
    {

    }
}
