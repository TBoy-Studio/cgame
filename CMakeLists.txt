cmake_minimum_required(VERSION 3.10)

project(tengine VERSION 1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Used by clang language server for code completion
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# Build as static lib
set(BUILD_SHARED_LIBS False)

# Build with all warnings enabled and optimize maximally
add_compile_options(-Wall -Wextra -Wpedantic -O3)

# Include directories for header files
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/deps/glfw/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/deps/glfw)

add_executable( ${PROJECT_NAME} 
    ${PROJECT_SOURCE_DIR}/src/main.c 
    ${PROJECT_SOURCE_DIR}/src/gl.c
    ${PROJECT_SOURCE_DIR}/src/shader.c
    ${PROJECT_SOURCE_DIR}/src/camera.c
    ${PROJECT_SOURCE_DIR}/src/window.c
)

target_link_libraries( ${PROJECT_NAME} PRIVATE m )