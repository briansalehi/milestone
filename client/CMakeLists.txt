file(GLOB source_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB qml_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qml)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.8.0 CONFIG REQUIRED COMPONENTS Core Qml Quick Network)
find_package(GTest 1.14.0 CONFIG)

qt_standard_project_setup(REQUIRES 6.5)
qt_add_executable(milestone ${source_files})
qt_add_qml_module(milestone URI Milestone VERSION 1.0 QML_FILES ${qml_files})
target_link_libraries(milestone PUBLIC Qt6::Core Qt6::Quick PRIVATE flashback)
target_include_directories(milestone PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/flashback/include)

install(TARGETS milestone RUNTIME)
