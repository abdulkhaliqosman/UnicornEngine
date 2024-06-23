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
	message("-Wall -Wno-c++98-compat -march=x86-64-v2")
    add_compile_options(-Wall -Wno-c++98-compat -march=x86-64-v2)
	# add_compile_definitions(UNICODE)
	if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
		message("UNICORN_MSVC_DEBUG")
		add_compile_definitions("_DEBUG")
	elseif("${CMAKE_BUILD_TYPE}" MATCHES "Release")
		message("UNICORN_MSVC_RELEASE")
	endif()

endif()

# Include sub-projects.
add_subdirectory ("extern")

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