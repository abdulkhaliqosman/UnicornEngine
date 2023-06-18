# src/client/CMakeLists.txt
cmake_minimum_required (VERSION 3.20)
message("hello from src/client/CMakeLists.txt")

set(UNICORN_CLIENT
    "client/unicornclient.cpp"
    )

set(UNICLIENT_WINDOWS
    "windows/windowsclient.h"
    "windows/windowsclient.cpp"
    )

add_library(Client
            "${UNICLIENT_WINDOWS}"
             "clientheader.h"
            )

target_include_directories(Client PRIVATE
            "${PROJECT_SOURCE_DIR}"
            "${PROJECT_SOURCE_DIR}/src/"
            "${PROJECT_SOURCE_DIR}/src/client"
            )
