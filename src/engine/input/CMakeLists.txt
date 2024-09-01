# src/gamecore/CMakeLists.txt
    
set(INPUT_MANAGER
    "manager/inputmanager.h" 
    "manager/inputmanager.cpp"
    )

set(INPUT_GAMEPAD
    "gamepad/gamepadinput.h"
    "gamepad/gamepadinput.cpp"
    )

set(INPUT_KEYBOARD
    "keyboard/keyboardinput.h"
    "keyboard/keyboardinput.cpp"
    "imgui/inputimguipage.h"
    "imgui/inputimguipage.cpp"
    )

add_library(Input
            "${INPUT_MANAGER}"
            "${INPUT_GAMEPAD}"
            "${INPUT_KEYBOARD}"
            
            )

target_include_directories(Input PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src"
                           "${PROJECT_SOURCE_DIR}/src/engine"
                           "${PROJECT_SOURCE_DIR}/src/engine/input"
                           "${PROJECT_SOURCE_DIR}/extern/imgui"
                           )

target_link_libraries(Input PRIVATE Core)
