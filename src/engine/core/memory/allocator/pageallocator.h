#pragma once
#include <cstdint>

namespace Unicorn
{
    class PageAllocator
    {
    public:
        void Startup();
        void Update();
        void Shutdown();

        void* Allocate(uint64_t size);
        void Deallocate();

    private:
        struct MemInfo
        {
            void* location;
            uint32_t size;
        };
        uint32_t m_AllocatedPageCount;
        uint32_t m_PageSize = 0;
    };
}
