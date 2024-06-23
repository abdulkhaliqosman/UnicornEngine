# src/gamecore/CMakeLists.txt

set(UNIGAMECORE_COMPONENT
    "component/component.h"
    "component/component.cpp"
    )

set(UNIGAMECORE_COMPONENTS
    "components/transformcomponent.h"
    "components/transformcomponent.cpp"
    "components/rendercomponent.h"
    "components/rendercomponent.cpp"
    )

set(UNIGAMECORE_ENTITY
    "entity/entity.h"
    "entity/entity.cpp"
    )

set(UNIGAMECORE_SCENE
    "scene/scene.h"
    "scene/scene.cpp"
    "scene/manager/scenemanager.h" 
    "scene/manager/scenemanager.cpp"
    "scene/imgui/sceneimguipage.h" 
    "scene/imgui/sceneimguipage.cpp"
    )

add_library(Gamecore
            "${UNIGAMECORE_COMPONENT}"
            "${UNIGAMECORE_COMPONENTS}"
            "${UNIGAMECORE_SCENE}"
            "${UNIGAMECORE_ENTITY}"
            "gamecoreheader.h"
            )

target_include_directories(Gamecore PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src"
                           "${PROJECT_SOURCE_DIR}/src/engine"
                           "${PROJECT_SOURCE_DIR}/src/engine/gamecore"
                           "${PROJECT_SOURCE_DIR}/extern/imgui"
                           )

target_link_libraries(Gamecore PRIVATE Core)
