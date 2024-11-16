file(GLOB source_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
file(GLOB header_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/flashback/*.hpp)
add_library(flashback SHARED ${source_files} ${header_files})
target_link_libraries(flashback PUBLIC pq pqxx)
target_include_directories(flashback PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB test_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
add_executable(test-flashback ${test_files})
target_link_libraries(test-flashback PUBLIC gtest gtest_main PRIVATE flashback)
target_compile_definitions(test-flashback PUBLIC PROGRAM_VERSION=${CMAKE_PROJECT_VERSION})
add_test(NAME test-flashback COMMAND test-flashback)

install(TARGETS flashback LIBRARY)
