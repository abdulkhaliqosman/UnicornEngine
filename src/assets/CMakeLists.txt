# src/assets/CMakeLists.txt

set(ASSETS_GEOMETRY
	"geometry/geometry.h"
	"geometry/cube.h"
	"geometry/cube.cpp"
	
	)

add_library(Assets 
            "assetsheader.h" 
            "${ASSETS_GEOMETRY}"
             )

target_include_directories(Assets PRIVATE 
              "${PROJECT_SOURCE_DIR}"
              "${PROJECT_SOURCE_DIR}/src/"
              "${PROJECT_SOURCE_DIR}/src/assets"
              )
