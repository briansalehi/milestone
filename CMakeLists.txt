cmake_minimum_required(VERSION 3.25)

set(project_version 0.3)

project(flashback VERSION ${project_version} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

file(GLOB source_files src/*.cpp)
file(GLOB qml_files ui/*.qml)

qt_add_executable(flashback ${source_files})

qt_add_qml_module(flashback
    URI flashback
    VERSION ${project_version}
    QML_FILES ${qml_files}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(flashback PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appflashback
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(flashback
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS flashback
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
