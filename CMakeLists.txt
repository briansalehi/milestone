cmake_minimum_required(VERSION 3.30.5)
project(Milestone VERSION 0.11.0 LANGUAGES CXX DESCRIPTION "Technical References Training Program")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_RPATH $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>)
#set(CMAKE_CXX_CLANG_TIDY /home/brian/.local/bin/clang-tidy -checks=-*,readability-*)

enable_testing()

add_subdirectory(importer)
add_subdirectory(flashback)
add_subdirectory(server)
add_subdirectory(client)
