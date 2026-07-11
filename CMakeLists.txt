cmake_minimum_required(VERSION 3.16)

project(ratatouile VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

include_directories(src)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(json)



qt_add_executable(appratatouile
    src/main.cpp
    src/Recipe.h
    src/RedBlackTree.h
    src/RedBlackTreeNode.h
    src/SplayTree.h
    src/TreeNode.h
)

qt_add_qml_module(appratatouile
    URI ratatouile
    QML_FILES
        src/Main.qml
    SOURCES
        src/data.h
        src/data.cpp
)

target_sources(appratatouile PRIVATE
    "datasets/normalized_recipes.json"
)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appratatouile PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appratatouile
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appratatouile
    PRIVATE Qt6::Quick
    PRIVATE nlohmann_json::nlohmann_json
)

install(TARGETS appratatouile
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
