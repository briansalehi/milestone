cmake_minimum_required(VERSION 3.25)

set(project_version 0.3)
project(Flashback VERSION ${project_version} LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

find_package(Boost COMPONENTS program_options)
find_package(GTest)
find_package(Qt6 6.5 REQUIRED COMPONENTS Quick WebView)

list(APPEND common_source src/flashcard.cpp)
list(APPEND common_test test/test-common.cpp)

add_library(common ${common_source})
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(test-common ${common_test})
target_link_libraries(test-common PRIVATE common gtest)

add_test(NAME common COMMAND $<TARGET_FILE:test-common>)

list(APPEND source_files main.cpp)
file(GLOB qml_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qml)

qt_standard_project_setup(REQUIRES 6.5)
qt_add_executable(flashback-gui ${source_files})
qt_add_qml_module(flashback-gui URI flashback VERSION 1.0 QML_FILES ${qml_files})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(flashback-gui PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.flashback-gui
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(flashback-gui PRIVATE Qt6::Quick Qt6::WebView)

include(GNUInstallDirs)

add_executable(validator src/validator.cpp)
target_include_directories(validator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(validator PRIVATE Boost::program_options pthread)

add_executable(test-validator test/test-validator.cpp)
target_include_directories(test-validator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test-validator PRIVATE gtest)

add_test(NAME validator COMMAND $<TARGET_FILE:test-validator>)

install(TARGETS flashback-gui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
