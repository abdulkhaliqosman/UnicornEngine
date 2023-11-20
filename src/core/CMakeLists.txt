# src/core/CMakeLists.txt

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
    )
    
set(UNICORE_MEMORY
    "memory/memory.h"
    "memory/manager/memorymanager.h"
    "memory/manager/memorymanager.cpp"
    )

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

set(UNICORE_THREAD
    "thread/thread.h"
    "thread/base/threadbase.h"
    "thread/job/jobthread.h"
    "thread/job/jobthread.cpp" 
    "thread/manager/threadmanager.h" 
    "thread/manager/threadmanager.cpp" 
     "thread/job/jobmanager.h" "thread/job/jobmanager.cpp" "thread/job/jobbase.h" "thread/mutex/mutex.h")

set(UNICORE_GAMEOBJECT
    "gameobject/gameobject.h"
    "gameobject/gameobject.cpp"
    )

set(UNICORE_COMPONENT
    "component/component.h"
    "component/component.cpp"
    )

set(UNICORE_FILESYSTEM
    "filesystem/filesystem.h"
    "filesystem/filesystem.cpp"
    )

set(UNICORE_SERIALIZER
    "serializer/serializer.h"
    "serializer/serializer.cpp"
    )

add_library(Core 
            "coreheader.h" 
            "${UNICORE_MATH}"
            "${UNICORE_THREAD}"
            "${UNICORE_MEMORY}"
            "${UNICORE_NETWORK}"
            "${UNICORE_GAMEOBJECT}"
            "${UNICORE_SERIALIZER}"
            "${UNICORE_INPUT}"
            "${UNICORE_FILESYSTEM}"
             "logging/log.h")

target_include_directories(Core PRIVATE
                        "${PROJECT_SOURCE_DIR}"
                        "${PROJECT_SOURCE_DIR}/src/"
                        "${PROJECT_SOURCE_DIR}/src/core"
                        )

target_link_libraries(Core PRIVATE Platform)