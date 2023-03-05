# src/core/CMakeLists.txt

set(UNICORE
    "core/core.h" 
    "core/core.cpp"
    )

set(UNICORE_MATH
    "math/matrix4f.h" 
    "math/vector4f.h"
    "math/quaternion4f.h"
    "math/transform.h"
    "math/color.h"
    "math/math.h")

set(UNICORE_THREAD
    "thread/thread.h"
    "thread/manager/threadmanager.h" 
    "thread/manager/threadmanager.cpp" 
    )

set(UNICORE_MEMORY
    "memory/memory.h"
    "memory/manager/memorymanager.h"
    "memory/manager/memorymanager.cpp"
    )

set(UNICORE_WINDOWS
    "windows/windowmanager/windowmanager.h"
    "windows/windowmanager/windowmanager.cpp"
    )

set(UNICORE_INPUT
    "input/inputmanager.h" 
    "input/inputmanager.cpp"
    )
    

add_library(Core 
            "coreheader.h" 
            "${UNICORE}"
            "${UNICORE_MATH}"
            "${UNICORE_THREAD}"
            "${UNICORE_MEMORY}"
            "${UNICORE_WINDOWS}"
            "${UNICORE_INPUT}"
             )

target_include_directories(Core PRIVATE
                        "${PROJECT_SOURCE_DIR}"
                        "${PROJECT_SOURCE_DIR}/src/"
                        "${PROJECT_SOURCE_DIR}/src/core"
                        )
