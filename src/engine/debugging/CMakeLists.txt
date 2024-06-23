# src/engine/debugging/CMakeLists.txt
    
set(UNIDEBUGGING_IMGUI
    "imgui/manager/imguimanager.h" 
    "imgui/manager/imguimanager.cpp"
    "imgui/page/imguipage.h" 
    "imgui/page/imguipage.cpp"
     "imgui/serializer/imguiserializer.h" "imgui/serializer/imguiserializer.cpp")

add_library(Debugging
            "${UNIDEBUGGING_IMGUI}"
            )

target_include_directories(Debugging PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/"
                           "${PROJECT_SOURCE_DIR}/src/engine"
                           "${PROJECT_SOURCE_DIR}/src/engine/debugging"
                           "${PROJECT_SOURCE_DIR}/extern/imgui"
                           )

target_link_libraries(Debugging PRIVATE Extern Core)
