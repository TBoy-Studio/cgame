include(CTest)

add_executable(test_memory test_memory.c)

target_link_libraries(test_memory cgame)
