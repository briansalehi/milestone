cmake_minimum_required(VERSION 3.15)
project(Flashback VERSION 0.1 LANGUAGES CXX)

find_package(Boost COMPONENTS program_options REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB source_files src/*)
file(GLOB header_files include/*)
file(GLOB doc_files docs/*)

add_executable(flashback)
target_sources(flashback PRIVATE ${source_files})
target_link_libraries(flashback PRIVATE Boost::program_options)
target_include_directories(flashback PRIVATE include)

enable_testing()

add_executable(practice)
target_sources(practice PRIVATE test/practice.cpp src/practice.cpp)
target_link_libraries(practice PRIVATE gtest)
target_include_directories(practice PRIVATE include)
add_test(NAME practice-test COMMAND practice)

add_executable(note)
target_sources(note PRIVATE test/note.cpp src/note.cpp)
target_link_libraries(note PRIVATE gtest)
target_include_directories(note PRIVATE include)
add_test(NAME note-test COMMAND note)

add_executable(book)
target_sources(book PRIVATE src/book.cpp test/book.cpp)
target_link_libraries(book PRIVATE gtest)
target_include_directories(book PRIVATE include test)
add_test(NAME book-test COMMAND book)

install(TARGETS flashback)
