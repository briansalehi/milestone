cmake_minimum_required(VERSION 4.0.0)
project("Milestone Client CLI" VERSION 0.1 LANGUAGES CXX DESCRIPTION "Command line interface implementation of milestone client")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ncurses CONFIG REQUIRED)

add_executable(milestone-cli main.cpp)
target_link_libraries(milestone-cli PRIVATE ncurses)
target_include_directories(milestone-cli PRIVATE include/)
target_compile_features(milestone-cli PRIVATE cxx_std_23)
