# src/engine/CMakeLists.txt

set(UNIENGINE_EDITOR
    "editor/server/editornetworkserver.h"
    "editor/server/editornetworkserver.cpp"
     "editor/commands/enginecommands.h")

add_library(Engine 
            "engine/engine.cpp"
            "${UNIENGINE_EDITOR}"
             "state/enginestatemachine.h" "editor/commands/enginecommands.h")

target_include_directories(Engine PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/"
                           "${PROJECT_SOURCE_DIR}/src/engine"
                           "${PROJECT_SOURCE_DIR}/extern/imgui"
                           )

target_link_libraries(Engine PRIVATE Core Render Assets)
