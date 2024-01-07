include(CTest)

add_executable(test_memory test_memory.c)
add_executable(test_scene test_scene.c)

target_link_libraries(test_memory cgame)
target_link_libraries(test_scene cgame)
