# src/editor/CMakeLists.txt
cmake_minimum_required (VERSION 3.20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(UNIEDITOR_EDITOR
    "editor/editor.h" 
    "editor/editor.cpp"
    "editor/serializer/editorserializer.h"
    "editor/serializer/editorserializer.cpp"
    )

set(UNIEDITOR_NETWORK
    "network/client/editornetworkclient.cpp"
    )

set(QT_ASSETBROWSER
    "qt/assetbrowser/qtassetbrowser.h"
    "qt/assetbrowser/qtassetbrowser.cpp"
    "qt/assetbrowser/qtassetbrowser.ui"
    )

set(QT_EDITORWINDOW
    "qt/editorwindow/qteditorwindow.h"
    "qt/editorwindow/qteditorwindow.cpp"
    "qt/editorwindow/qteditorwindow.ui"
    )

set(QT_OBJECTHIERARCHY
    "qt/objecthierarchy/qtobjecthierarchy.h"
    "qt/objecthierarchy/qtobjecthierarchy.cpp"
    "qt/objecthierarchy/qtobjecthierarchy.ui"
    )

set(QT_PROPERTYINSPECTOR
    "qt/property/inspector/qtpropertyinspector.h"
    "qt/property/inspector/qtpropertyinspector.cpp"
    "qt/property/inspector/qtpropertyinspector.ui"
    )

set(QT_SCENEVIEWER
    "qt/sceneviewer/qtsceneviewer.h"
    "qt/sceneviewer/qtsceneviewer.cpp"
    "qt/sceneviewer/qtsceneviewer.ui"
    )



add_library(Editor 
            "editorheader.h"
            "${UNIEDITOR_EDITOR}"
            "${UNIEDITOR_NETWORK}"
            "${QT_ASSETBROWSER}"
            "${QT_EDITORWINDOW}"
            "${QT_OBJECTHIERARCHY}"
            "${QT_PROPERTYINSPECTOR}"
            "${QT_SCENEVIEWER}" "editor/objecthierarchy/objecthierarchyeditor.h" "editor/objecthierarchy/objecthiearchyeditor.cpp" "commands/editorcommands.h" "commands/editorcommands.cpp")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_include_directories(Editor PRIVATE
                        "${PROJECT_BINARY_DIR}"
                        "${PROJECT_SOURCE_DIR}"
                        "${PROJECT_SOURCE_DIR}/src/"
                        "${PROJECT_SOURCE_DIR}/src/editor"
                        )

target_link_libraries(Editor Qt5::Widgets)
