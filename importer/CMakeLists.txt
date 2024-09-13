find_package(Boost CONFIG REQUIRED COMPONENTS program_options system)

file(GLOB source_files RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} src/main.cpp)
add_executable(importer ${source_files})
target_link_libraries(importer PUBLIC Boost::program_options pq pqxx)
target_include_directories(importer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(importer PRIVATE PROGRAM_VERSION="${CMAKE_PROJECT_VERSION}")

add_executable(test-importer EXCLUDE_FROM_ALL test/importer.cpp ${source_files})
target_link_libraries(test-importer PUBLIC gtest program_options pq pqxx)
target_include_directories(test-importer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME test-importer COMMAND test-importer)
