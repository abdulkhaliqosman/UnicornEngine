# src/platform/CMakeLists.txt

set(UNIPLATFORM_WINDOWS
    "windows/windowsplatform.h"
    "windows/windowsplatform.cpp"
    )
    
add_library(Platform 
            "${UNIPLATFORM_WINDOWS}"
            )

target_include_directories(Platform PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/"
                           "${PROJECT_SOURCE_DIR}/src/engine/"
                           "${PROJECT_SOURCE_DIR}/src/engine/platform"
                           "${PROJECT_SOURCE_DIR}/extern/imgui"
                           )