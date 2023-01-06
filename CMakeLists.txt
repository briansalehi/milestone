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

### libraries ###

add_library(note SHARED src/note.cpp)
target_include_directories(note PUBLIC include)

add_library(practice SHARED EXCLUDE_FROM_ALL src/practice.cpp)
target_include_directories(practice PUBLIC include)

add_library(book SHARED src/book.cpp)
target_link_libraries(book PUBLIC note)
target_include_directories(book PUBLIC include)

add_library(markdown_note_builder SHARED src/markdown_note_builder.cpp)
target_link_libraries(markdown_note_builder PUBLIC note)
target_include_directories(book PUBLIC include)

add_library(markdown_book_builder SHARED src/markdown_book_builder.cpp)
target_link_libraries(markdown_book_builder PUBLIC note book)
target_include_directories(markdown_book_builder PUBLIC include)

add_library(menu SHARED src/menu.cpp)
target_link_libraries(menu PUBLIC markdown_book_builder)
target_include_directories(menu PUBLIC include)

### test executables ###

add_executable(test_practice EXCLUDE_FROM_ALL)
target_sources(test_practice PRIVATE test/practice.cpp)
target_link_libraries(test_practice PRIVATE gtest PUBLIC practice)
target_include_directories(test_practice PUBLIC include PRIVATE test)
#add_test(NAME practice_test COMMAND practice)

add_executable(test_note)
target_sources(test_note PRIVATE test/note.cpp PUBLIC src/note.cpp)
target_link_libraries(test_note PRIVATE gtest note)
target_include_directories(test_note PUBLIC include PRIVATE test)
add_test(NAME test_note COMMAND test_note)

add_executable(test_book)
target_sources(test_book PRIVATE test/book.cpp PUBLIC src/book.cpp)
target_link_libraries(test_book PRIVATE gtest book)
target_include_directories(test_book PUBLIC include PRIVATE test)
add_test(NAME test_book COMMAND test_book)

add_executable(test_markdown_note_builder)
target_sources(test_markdown_note_builder PRIVATE test/markdown_note_builder.cpp PUBLIC src/markdown_note_builder.cpp)
target_link_libraries(test_markdown_note_builder PRIVATE gtest note)
target_include_directories(test_markdown_note_builder PUBLIC include PRIVATE test)
add_test(NAME test_markdown_note_builder COMMAND test_markdown_note_builder)

add_executable(test_markdown_book_builder)
target_sources(test_markdown_book_builder PRIVATE test/markdown_book_builder.cpp PUBLIC src/markdown_book_builder.cpp)
target_link_libraries(test_markdown_book_builder PRIVATE gtest PUBLIC markdown_note_builder note book)
target_include_directories(test_markdown_book_builder PUBLIC include PRIVATE test)
add_test(NAME test_markdown_book_builder COMMAND test_markdown_book_builder)


### installation targets ###

install(TARGETS flashback)
