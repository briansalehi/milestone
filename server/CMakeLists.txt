find_package(Boost CONFIG REQUIRED COMPONENTS program_options system)

file(GLOB source_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)

add_executable(server ${source_files})
target_link_libraries(server PUBLIC Boost::system Boost::program_options)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(server PRIVATE PROGRAM_VERSION=${CMAKE_PROJECT_VERSION})

file(GLOB test_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
list(REMOVE_ITEM source_files src/main.cpp)
list(APPEND test_files ${source_files})
message(NOTICE "${test_files}")

add_executable(test-server ${test_files})
target_link_libraries(test-server PRIVATE Boost::program_options gtest gtest_main)
target_include_directories(test-server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(test-server PRIVATE PROGRAM_VERSION=${CMAKE_PROJECT_VERSION})
add_test(NAME test-server COMMAND test-server)
