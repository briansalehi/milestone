cmake_minimum_required(VERSION 3.15)
project(Flashback VERSION 0.1 LANGUAGES CXX)

file(GLOB source_files src/*)
file(GLOB header_files include/*)
file(GLOB doc_files docs/*)

add_executable(flashback)
target_sources(flashback ${source_files})
