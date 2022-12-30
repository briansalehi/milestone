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

add_executable(practice EXCLUDE_FROM_ALL)
target_sources(practice PRIVATE test/practice.cpp PUBLIC src/practice.cpp)
target_link_libraries(practice PRIVATE gtest)
target_include_directories(practice PUBLIC include PRIVATE test)
#add_test(NAME practice_test COMMAND practice)

add_executable(note)
target_sources(note PRIVATE test/note.cpp PUBLIC src/note.cpp)
target_link_libraries(note PRIVATE gtest)
target_include_directories(note PUBLIC include PRIVATE test)
add_test(NAME note_test COMMAND note)

add_executable(book)
target_sources(book PRIVATE test/book.cpp PUBLIC src/book.cpp)
target_link_libraries(book PRIVATE gtest)
target_include_directories(book PUBLIC include PRIVATE test)
add_test(NAME book_test COMMAND book)

add_executable(markdown_note_builder)
target_sources(markdown_note_builder PRIVATE test/markdown_note_builder.cpp PUBLIC src/markdown_note_builder.cpp)
target_link_libraries(markdown_note_builder PRIVATE gtest)
target_include_directories(markdown_note_builder PUBLIC include PRIVATE test)
add_test(NAME markdown_note_builder_test COMMAND markdown_note_builder)

add_executable(markdown_resource_builder)
target_sources(markdown_resource_builder PRIVATE test/markdown_resource_builder.cpp PUBLIC src/markdown_resource_builder.cpp src/book.cpp)
target_link_libraries(markdown_resource_builder PRIVATE gtest)
target_include_directories(markdown_resource_builder PUBLIC include PRIVATE test)
add_test(NAME markdown_resource_builder_test COMMAND markdown_resource_builder)

install(TARGETS flashback)
