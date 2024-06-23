# src/engine/CMakeLists.txt

add_subdirectory ("platform")
add_subdirectory ("core")
add_subdirectory ("assets")
add_subdirectory ("render")
add_subdirectory ("debugging")
add_subdirectory ("input")
add_subdirectory ("animation")
add_subdirectory ("gamecore")

set(UNIENGINE_EDITOR
    "editor/server/editornetworkserver.h"
    "editor/server/editornetworkserver.cpp"
     "editor/commands/enginecommands.h")

add_library(Engine 
            "engine.cpp"
            "${UNIENGINE_EDITOR}"
            "state/enginestatemachine.h" "editor/commands/enginecommands.h")

target_include_directories(Engine PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/"
                           "${PROJECT_SOURCE_DIR}/src/engine"
                           "${PROJECT_SOURCE_DIR}/extern/imgui"
                           )

target_link_libraries(Engine PRIVATE Core Assets Render Debugging Input Gamecore)
