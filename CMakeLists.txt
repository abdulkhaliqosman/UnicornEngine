# UnicornEngine/CMakeLists.txt
# Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

project (UnicornEngine)

if (MSVC)
#     # warning level 4
# 	message("add_compile_options(/W4)")
#     add_compile_options(/W4)
# else()
    # additional warnings
	message("-Wall -Wextra -Wpedantic -Wno-c++98-compat -march=x86-64-v2")
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-c++98-compat -march=x86-64-v2)
endif()

# Include sub-projects.
add_subdirectory ("src")

set(UNICORN_SHADERS_DIR
	"content/shaders"
	)


set(UNICORN_CONTENT
	"content/"
	)

# file(GLOB files "${UNICORN_SHADERS_DIR}/*.hlsl" )
# foreach(file ${files})
# 	file(RELATIVE_PATH RelPath ${CMAKE_CURRENT_SOURCE_DIR} ${file})
# 	message("from: ${RelPath}, to: ${CMAKE_CURRENT_BINARY_DIR}/src/${RelPath}")
# 
# 	 configure_file("${file}"
# 	 			   "${CMAKE_CURRENT_BINARY_DIR}/src/${RelPath}"
# 	 			   COPYONLY
# 	 			   )
# endforeach()

# install(TARGETS UnicornClient DESTINATION "bin")