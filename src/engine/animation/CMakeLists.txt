# src/engine/animation/CMakeLists.txt

set(UNIANIM_MANAGER
    "manager/animationmanager.h"
    "manager/animationmanager.cpp"
    )

set(UNIANIM_OBJECT
    "object/animobject.h"
    "object/animobject.cpp"
    )

set(UNISKELETON_OBJECT
    "skeleton/skeletonobject.h"
    "skeleton/skeletonobject.cpp"
    )

add_library(Animation 
            "${UNIANIM_MANAGER}"
            "${UNIANIM_OBJECT}"
            )

target_include_directories(Animation PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/"
                           "${PROJECT_SOURCE_DIR}/src/engine"
                           "${PROJECT_SOURCE_DIR}/src/engine/animation"
                           )
                           
