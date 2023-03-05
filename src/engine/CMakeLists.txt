# src/engine/CMakeLists.txt

add_library(Engine "engine/engine.cpp")

target_include_directories(Engine PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/"
                           "${PROJECT_SOURCE_DIR}/src/engine"
                           )

target_link_libraries(Engine PRIVATE Core Render Assets)
