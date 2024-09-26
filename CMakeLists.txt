cmake_minimum_required(VERSION 3.30)
project(Milestone VERSION 0.5 LANGUAGES CXX DESCRIPTION "Knowledge Training Application")

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_CLANG_TIDY /home/brian/.local/bin/clang-tidy -checks=-*,readability-*)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

find_package(GTest REQUIRED)

add_subdirectory(importer)
add_subdirectory(flashback)
add_subdirectory(server)
add_subdirectory(client)
