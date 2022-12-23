cmake_minimum_required(VERSION 3.15)
project(Flashback VERSION 0.1 LANGUAGES CXX)

find_package(Boost COMPONENTS program_options REQUIRED)

file(GLOB source_files src/*)
file(GLOB header_files include/*)
file(GLOB doc_files docs/*)

add_executable(flashback)
target_sources(flashback PRIVATE ${source_files})
target_link_libraries(flashback PRIVATE Boost::program_options)
target_include_directories(flashback PRIVATE include)

enable_testing()

add_executable(practice EXCLUDE_FROM_ALL)
target_sources(practice PRIVATE test/practice.cpp src/practice.cpp)
target_link_libraries(practice PRIVATE gtest)
target_include_directories(practice PRIVATE include)
add_test(NAME practice COMMAND practice)

install(TARGETS flashback)
