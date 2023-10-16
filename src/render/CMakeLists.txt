# src/render/CMakeLists.txt

set(RENDER_MANAGER
    "manager/rendermanager.h"
    "manager/rendermanager.cpp"
	)

set(RENDER_COMPONENT
    "component/rendercomponent.h"
    "component/rendercomponent.cpp"
	)

add_library(Render
            "renderheader.h"
            "${RENDER_MANAGER}"
            "${RENDER_COMPONENT}"
             "camera/cameraobject.h" "camera/cameraobject.cpp")

target_include_directories(Render PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/"
                           "${PROJECT_SOURCE_DIR}/src/render"
                           )

target_link_libraries(Render PRIVATE Core)
