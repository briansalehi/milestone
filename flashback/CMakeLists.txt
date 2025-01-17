find_package(PostgreSQL 16.4.0 REQUIRED)
find_package(GTest 1.14.0 CONFIG)

file(GLOB source_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
file(GLOB header_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/flashback/*.hpp)
add_library(flashback STATIC ${source_files} ${header_files})
target_link_libraries(flashback PRIVATE pq pqxx)
target_include_directories(flashback PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB test_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
add_executable(test-flashback ${test_files})
target_link_libraries(test-flashback PRIVATE gtest gtest_main flashback)
target_compile_definitions(test-flashback PUBLIC PROGRAM_VERSION="${CMAKE_PROJECT_VERSION}")
add_test(NAME test-flashback COMMAND test-flashback)

install(TARGETS flashback LIBRARY)
