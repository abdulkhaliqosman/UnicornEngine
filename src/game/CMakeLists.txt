# src/game/CMakeLists.txt

add_library(Game
            "testgame/testscene.h"
            "testgame/testscene.cpp"
            "testgame/components/fpscameracontroller.h" 
            "testgame/components/fpscameracontroller.cpp"
            )

target_include_directories(Game PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/"
                           )

target_link_libraries(Game PRIVATE Engine)