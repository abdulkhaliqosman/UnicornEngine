# src/engine/CMakeLists.txt

set(UNIENGINE_EDITOR
    "editor/server/editornetworkserver.h"
    "editor/server/editornetworkserver.cpp"
    )

set(UNIENGINE_SCENE
    "scene/scene.h"
    "scene/scene.cpp"
    )

add_library(Engine 
            "engine/engine.cpp"
            "${UNIENGINE_EDITOR}"
            "${UNIENGINE_SCENE}"
             "state/enginestatemachine.h")

target_include_directories(Engine PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/"
                           "${PROJECT_SOURCE_DIR}/src/engine"
                           )

target_link_libraries(Engine PRIVATE Core Render Assets)
