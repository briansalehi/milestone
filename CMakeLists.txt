cmake_minimum_required(VERSION 3.25)

project(flashback VERSION 0.3 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(components Widgets LinguistTools WebEngineWidgets)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS ${components})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${components})

file(GLOB source_files src/*.cpp)
file(GLOB header_files include/flashback/*.hpp)
file(GLOB ui_files ui/*.ui)
file(GLOB ts_files ts/*.ts)

set(PROJECT_SOURCES ${source_files} ${header_files} ${ui_files} ${ts_files})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(flashback MANUAL_FINALIZATION ${PROJECT_SOURCES})
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${ts_files})

    # Define target properties for Android with Qt 6 as:
    #   set_property(TARGET flashback APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(flashback SHARED ${PROJECT_SOURCES})
        # Define properties for Android with Qt 5 after find_package() calls as:
        #  set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(flashback ${PROJECT_SOURCES})
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${ts_files})
endif()

target_link_libraries(flashback PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.flashback)
endif()

set_target_properties(flashback PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS flashback
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(flashback)
endif()
