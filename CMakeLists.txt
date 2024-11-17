cmake_minimum_required(VERSION 3.30)
project(Milestone VERSION 0.8 LANGUAGES CXX DESCRIPTION "Technical References Training Program")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib64)
#set(CMAKE_CXX_CLANG_TIDY /home/brian/.local/bin/clang-tidy -checks=-*,readability-*)

find_package(GTest 1.14.0 REQUIRED)
find_package(Boost 1.80.0 REQUIRED COMPONENTS program_options system)
find_package(PostgreSQL 16.4.0 REQUIRED)
find_package(Qt6 6.8.0 REQUIRED COMPONENTS Core Qml Quick Network)

enable_testing()

add_subdirectory(importer)
add_subdirectory(flashback)
add_subdirectory(server)
add_subdirectory(client)
