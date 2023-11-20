# src/render/CMakeLists.txt

set(RENDER_CAMERA
    "camera/cameraobject.h"
    "camera/cameraobject.cpp"
	)

set(RENDER_COMPONENT
    "component/rendercomponent.h"
    "component/rendercomponent.cpp"
	)

set(RENDER_MANAGER
    "manager/rendermanager.h"
    "manager/rendermanager.cpp"
	)
    
set(RENDER_OBJECT
    "object/renderobject.h"
    "object/renderobject.cpp"
	)

add_library(Render
            "renderheader.h"
            "${RENDER_MANAGER}"
            "${RENDER_COMPONENT}"
            "${RENDER_OBJECT}"
             "camera/cameraobject.h" "camera/cameraobject.cpp" "object/renderobject.h")

target_include_directories(Render PRIVATE 
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/"
                           "${PROJECT_SOURCE_DIR}/src/render"
                           )

target_link_libraries(Render PRIVATE Core)
