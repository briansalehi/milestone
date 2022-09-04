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

install(TARGETS flashback)
