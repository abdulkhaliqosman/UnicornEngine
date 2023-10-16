# extern/CMakeLists.txt

# Add source to this project's executable.

set(EXTERN_CGLTF
	"cgltf/cgltf.h"
	"cgltf/cgltf.c"
	)

set(EXTERN_STBIMAGE
	"stb_image/stb_image.h"
	"stb_image/stb_image.c"
	)

add_library(Extern
			"${EXTERN_CGLTF}"
			"${EXTERN_STBIMAGE}"
			 )

target_include_directories(Extern PRIVATE 
              "${PROJECT_SOURCE_DIR}"
              "${PROJECT_SOURCE_DIR}/extern/"
              )
# TODO: Add tests and install targets if needed.
