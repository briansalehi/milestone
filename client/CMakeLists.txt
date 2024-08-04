file(GLOB source_files RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB qml_files RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} *.qml)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

qt_standard_project_setup(REQUIRES 6.5)
qt_add_executable(milestone ${source_files})
qt_add_qml_module(milestone URI Milestone VERSION 1.0 QML_FILES Main.qml)
target_link_libraries(milestone PRIVATE Qt6::Core Qt6::Quick)
target_include_directories(milestone PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS milestone)
