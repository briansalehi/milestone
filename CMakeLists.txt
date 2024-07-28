cmake_minimum_required(VERSION 3.30)
project(Milestone VERSION 0.4 LANGUAGES CXX DESCRIPTION "Knowledge Training Application")

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

find_package(Boost COMPONENTS program_options)
find_package(GTest)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Quick Controls WebView)
find_package(Qt${QT_MAJOR_VERSION} REQUIRED COMPONENTS Core Quick Controls WebView)

file(GLOB common_source RELATIVE src/*.cpp)
file(GLOB common_test   RELATIVE test/*.cpp)

add_library(common ${common_source})
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(test-common ${common_test})
target_link_libraries(test-common PRIVATE common gtest)

add_test(NAME common COMMAND $<TARGET_FILE:test-common>)

list(APPEND source_files main.cpp)
file(GLOB qml_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qml)

qt_standard_project_setup(REQUIRES 6.5)
qt_add_executable(flashback ${source_files})
qt_add_qml_module(flashback URI flashback VERSION 1.0 QML_FILES ${qml_files})

set_target_properties(flashback PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.milestone.project
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
target_compile_definitions(flashback PRIVATE PROGRAM_VERSION="${CMAKE_PROJECT_VERSION}")
target_link_libraries(flashback PRIVATE Qt6::Quick Qt6::WebView)

include(GNUInstallDirs)

install(TARGETS flashback
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
