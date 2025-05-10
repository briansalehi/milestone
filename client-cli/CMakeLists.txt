cmake_minimum_required(VERSION 4.0.0)
project("Milestone Command Line Client" VERSION 0.1 LANGUAGES CXX DESCRIPTION "Milestone Command Line Client")

include(GNUInstallDirs)
enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_INSTALL_RPATH $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>)

find_package(Curses REQUIRED)
find_package(Boost CONFIG COMPONENTS system program_options REQUIRED)

file(GLOB client_source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
add_executable(milestone-cli ${client_source})
target_link_libraries(milestone-cli PRIVATE curses Boost::system Boost::program_options)
target_include_directories(milestone-cli PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_definitions(milestone-cli PRIVATE PROGRAM_VERSION="${PROJECT_VERSION}")
