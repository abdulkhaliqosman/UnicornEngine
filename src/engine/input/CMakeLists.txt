# src/gamecore/CMakeLists.txt
    

set(UNINPUT_MANAGER
    "manager/inputmanager.h" 
    "manager/inputmanager.cpp"
    )

add_library(Input
            "${UNINPUT_MANAGER}"
             "inputheader.h")

target_include_directories(Input PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src"
                           "${PROJECT_SOURCE_DIR}/src/engine"
                           "${PROJECT_SOURCE_DIR}/src/engine/input"
                           )

target_link_libraries(Input PRIVATE Core)
