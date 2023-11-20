# src/assets/CMakeLists.txt

set(ASSETS_ANIMATION
	"animation/animclip.h"
	"animation/animtrack.h"
    )

set(ASSETS_GEOMETRY
	"geometry/geometry.h"
	"geometry/cube.h"
	"geometry/cube.cpp"
    )

set(ASSETS_MESH
	"mesh/meshdata.h"
	"mesh/meshdata.cpp"
    )

set(ASSETS_FILE
    "file/fbx/fbxfileasset.h"
    "file/fbx/fbxfileasset.cpp"
    "file/gltf/gltffileasset.h"
    "file/gltf/gltffileasset.cpp"
    )

add_library(Assets 
            "assetsheader.h" 
            # "${ASSETS_ANIMATION}"
            "${ASSETS_GEOMETRY}"
            "${ASSETS_MESH}"
            "${ASSETS_FILE}"
             "file/assetfiledata.h" "geometry/vertex.h")

target_include_directories(Assets PRIVATE 
              "${PROJECT_SOURCE_DIR}"
              "${PROJECT_SOURCE_DIR}/src/"
              "${PROJECT_SOURCE_DIR}/src/assets"
              )
