# src/CMakeLists.txt

# Add source to this project's executable.

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

if("${UNICORN_BUILD_TYPE}" MATCHES "Editor")
    message("UNICORN_EDITOR")
    add_compile_definitions(UNICORN_EDITOR)
elseif("${UNICORN_BUILD_TYPE}" MATCHES "Client")
    message("UNICORN_CLIENT")
    add_compile_definitions(UNICORN_CLIENT)
endif()

add_subdirectory ("core")
add_subdirectory ("assets")
add_subdirectory ("render")

add_subdirectory("engine")

if("${UNICORN_BUILD_TYPE}" MATCHES "Editor")
    add_subdirectory("editor")
    
    add_executable(UnicornEditor "editor/unicorneditor.cpp")

    target_include_directories(UnicornEditor PUBLIC
                               "${PROJECT_BINARY_DIR}"
                               "${PROJECT_SOURCE_DIR}"
                               "${PROJECT_SOURCE_DIR}/src/"
                               "${PROJECT_SOURCE_DIR}/src/editor"
                               )

    target_link_libraries(UnicornEditor PUBLIC Engine Editor)
    
elseif("${UNICORN_BUILD_TYPE}" MATCHES "Client")
    add_subdirectory("client")

    add_executable (UnicornClient "client/unicornclient.cpp")

    target_include_directories(UnicornClient PUBLIC
                               "${PROJECT_BINARY_DIR}"
                               "${PROJECT_SOURCE_DIR}"
                               "${PROJECT_SOURCE_DIR}/src/"
                               "${PROJECT_SOURCE_DIR}/src/client"
                               )

    target_link_libraries(UnicornClient PUBLIC Engine Client)
endif()

# TODO: Add tests and install targets if needed.
