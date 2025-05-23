cmake_minimum_required(VERSION 4.0.0)
project("Milestone Client" VERSION 0.1 LANGUAGES CXX DESCRIPTION "Milestone Graphical Client")

include(GNUInstallDirs)
enable_testing()

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 6.9.0 CONFIG REQUIRED COMPONENTS Core Qml Quick WebView)

file(GLOB source_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB qml_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qml)

qt_standard_project_setup(REQUIRES 6.5)
add_executable(milestone)
target_sources(milestone PRIVATE ${source_files})
qt_add_qml_module(milestone URI Milestone VERSION 1.0 QML_FILES ${qml_files})
target_link_libraries(milestone PUBLIC Qt6::Core Qt6::Qml Qt6::Quick Qt6::WebView PRIVATE flashback)
target_include_directories(milestone PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/flashback/include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/ClientConfig.cmake COMPATIBILITY SameMajorVersion)

install(TARGETS milestone EXPORT Client COMPONENT Client:: RUNTIME CONFIGURATIONS Release MinSizeRel)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ClientConfig.cmake CONFIGURATIONS Release MinSizeRel DESTINATION ${CMAKE_INSTALL_LIBDIR}/milestone/cmake)

set(CPACK_PACKAGE_VENDOR "Brian Salehi <briansalehi@proton.me>")
set(CPACK_PACKAGE_CONTACT "briansalehi@proton.me")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Milestone Project User Interface")
string(TOLOWER ${CMAKE_PROJECT_NAME} CMAKE_PROJECT_NAME)
string(TOLOWER ${CMAKE_SYSTEM_NAME} CMAKE_SYSTEM_NAME)

include(CPack)
