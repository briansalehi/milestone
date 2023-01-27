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

########## libraries ##########

add_library(note SHARED src/note.cpp)
target_include_directories(note PUBLIC include)

add_library(console SHARED src/console.cpp)
target_include_directories(console PUBLIC include)

add_library(book SHARED src/book.cpp)
target_link_libraries(book PUBLIC note)
target_include_directories(book PUBLIC include)

add_library(reference SHARED src/reference.cpp)
target_include_directories(reference PUBLIC include)

add_library(practice SHARED src/practice.cpp)
target_link_libraries(practice PUBLIC reference)
target_include_directories(practice PUBLIC include)

add_library(topic SHARED src/topic.cpp)
target_link_libraries(topic PUBLIC practice)
target_include_directories(topic PUBLIC include)

add_library(subject SHARED src/subject.cpp)
target_link_libraries(subject PUBLIC topic)
target_include_directories(subject PUBLIC include)

add_library(resource_loader SHARED src/resource_loader.cpp)
target_link_libraries(resource_loader PRIVATE pq pqxx PUBLIC book)
target_include_directories(resource_loader PUBLIC include)

add_library(library SHARED src/library.cpp)
target_link_libraries(library PUBLIC resource_loader console)
target_include_directories(library PUBLIC include)

add_library(trainer SHARED src/trainer.cpp)
target_link_libraries(trainer PRIVATE pq pqxx PUBLIC console)
target_include_directories(trainer PUBLIC include)

add_library(dashboard SHARED src/dashboard.cpp)
target_link_libraries(dashboard PUBLIC library trainer resource_loader)
target_include_directories(dashboard PUBLIC include)

add_library(practice_collection SHARED src/practice_collection.cpp)
target_link_libraries(practice_collection PUBLIC console practice)
target_include_directories(practice_collection PUBLIC include)

########## test executables ##########

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

add_executable(test_library)
target_sources(test_library PUBLIC test/library.cpp)
target_link_libraries(test_library PRIVATE gtest library)
target_include_directories(test_library PUBLIC include PRIVATE test)
add_test(NAME test_library COMMAND test_library)

add_executable(test_resource_loader)
target_sources(test_resource_loader PUBLIC test/resource_loader.cpp)
target_link_libraries(test_resource_loader PUBLIC resource_loader PRIVATE gtest)
target_include_directories(test_resource_loader PUBLIC include PRIVATE test)
add_test(NAME test_resource_loader COMMAND test_resource_loader)

add_executable(test_dashboard)
target_sources(test_dashboard PUBLIC test/dashboard.cpp)
target_link_libraries(test_dashboard PRIVATE gtest dashboard)
target_include_directories(test_dashboard PUBLIC include PRIVATE test)
add_test(NAME test_dashboard COMMAND test_dashboard)

### installation targets ###

install(TARGETS flashback)
