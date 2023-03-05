# src/CMakeLists.txt

# Add source to this project's executable.

add_subdirectory ("core")
add_subdirectory ("assets")
add_subdirectory ("render")

add_subdirectory("engine")

add_executable (UnicornEngine "UnicornEngine.cpp")
target_include_directories(UnicornEngine PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/"
                           )


target_link_libraries(UnicornEngine PUBLIC Engine)
# TODO: Add tests and install targets if needed.
