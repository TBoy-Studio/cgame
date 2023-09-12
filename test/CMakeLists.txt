include(CTest)

add_executable(test_memory test_memory.c)
add_executable(test_file test_file.c)

target_link_libraries(test_memory cgame)
target_link_libraries(test_file cgame)
