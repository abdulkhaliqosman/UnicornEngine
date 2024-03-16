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

set(EXTERN_IMGUI
	"imgui/imgui.cpp"
	"imgui/imgui.h"
	"imgui/imgui_demo.cpp"
	"imgui/imgui_draw.cpp"
	"imgui/imgui_tables.cpp"
	"imgui/imgui_widgets.cpp"
	"imgui/backends/imgui_impl_dx11.cpp"
	"imgui/backends/imgui_impl_dx11.h"
	"imgui/backends/imgui_impl_win32.cpp"
	"imgui/backends/imgui_impl_win32.h"
	)

add_library(Extern
			"${EXTERN_CGLTF}"
			"${EXTERN_STBIMAGE}"
			"${EXTERN_IMGUI}"
			 )

target_include_directories(Extern PRIVATE 
              "${PROJECT_SOURCE_DIR}"
              "${PROJECT_SOURCE_DIR}/extern/"
              "${PROJECT_SOURCE_DIR}/extern/imgui"
              )
# TODO: Add tests and install targets if needed.
