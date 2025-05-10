cmake_minimum_required(VERSION 4.0.0)
project(Milestone VERSION 0.12.0 LANGUAGES CXX DESCRIPTION "Technical References Training Program")

include(GNUInstallDirs)
enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_RPATH $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>)
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

add_subdirectory(flashback)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(client-cli)
