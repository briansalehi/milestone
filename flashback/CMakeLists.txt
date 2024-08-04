file(GLOB source_files RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)

add_library(flashback SHARED ${source_files})
target_link_libraries(flashback PUBLIC Boost::program_options)
target_include_directories(flashback PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(flashback PUBLIC PROGRAM_VERSION=${CMAKE_PROJECT_VERSION})

file(GLOB test_files RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
add_executable(test-flashback EXCLUDE_FROM_ALL ${test_files} ${source_files})
target_link_libraries(test-flashback PUBLIC gtest)
target_include_directories(test-flashback PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(flashback PUBLIC PROGRAM_VERSION=${CMAKE_PROJECT_VERSION})
add_test(NAME test-flashback COMMAND test-flashback)

install(TARGETS flashback LIBRARY)
