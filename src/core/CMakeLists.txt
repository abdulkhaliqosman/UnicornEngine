# src/core/CMakeLists.txt

set(UNICORE_COMPONENT
    "component/component.h"
    "component/component.cpp"
    )

set(UNICORE_FILESYSTEM
    "filesystem/filesystem.h"
    "filesystem/filesystem.cpp"
    )

set(UNICORE_INPUT
    "input/inputmanager.h" 
    "input/inputmanager.cpp"
    )

set(UNICORE_MATH
    "math/matrix4x4f.h" 
    "math/vector4f.h"
    "math/quaternion4f.h"
    "math/transform.h"
    "math/color.h"
    "math/math.h"
    "math/projection.h"
     "math/eulerangles.h")
    
set(UNICORE_MEMORY
    "memory/memory.h"
    "memory/manager/memorymanager.h"
    "memory/manager/memorymanager.cpp"
    "memory/allocator/memoryallocator.h" 
    "memory/allocator/memoryallocator.cpp" 
    "memory/allocator/pageallocator.h"
    "memory/allocator/pageallocator.cpp"
     "memory/allocator/blockallocator.h" "memory/allocator/blockallocator.cpp" "memory/allocator/buddyallocator.h" "memory/allocator/buddyallocator.cpp")

set(UNICORE_NETWORK
    "network/base/networkbase.h"
    "network/base/networkbase.cpp"
    "network/client/networkclient.h"
    "network/client/networkclient.cpp"
    "network/server/networkserver.h"
    "network/server/networkserver.cpp"
    "network/thread/networkthread.h"
    "network/thread/networkthread.cpp"
    )

set(UNICORE_SERIALIZER
    "serializer/serializer.h"
    "serializer/serializer.cpp"
    )

set(UNICORE_THREAD
    "thread/thread.h"
    "thread/base/threadbase.h"
    "thread/job/jobthread.h"
    "thread/job/jobthread.cpp" 
    "thread/manager/threadmanager.h" 
    "thread/manager/threadmanager.cpp" 
    "thread/job/jobmanager.h" 
    "thread/job/jobmanager.cpp" 
    "thread/job/jobbase.h" 
    "thread/mutex/mutex.h"
    )



add_library(Core 
            "coreheader.h" 
            "${UNICORE_MATH}"
            "${UNICORE_THREAD}"
            "${UNICORE_MEMORY}"
            "${UNICORE_NETWORK}"
            "${UNICORE_SERIALIZER}"
            "${UNICORE_INPUT}"
            "${UNICORE_FILESYSTEM}"
             "logging/log.h"
             )

target_include_directories(Core PRIVATE
                        "${PROJECT_SOURCE_DIR}"
                        "${PROJECT_SOURCE_DIR}/src/"
                        "${PROJECT_SOURCE_DIR}/src/core"
                        )

target_link_libraries(Core PRIVATE Platform)