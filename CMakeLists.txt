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

add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/TEngine-Camera)
add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/TEngine-Shader)
add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/TEngine-Window)

# Include directories for header files
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/submodules/TEngine-Camera/include)
include_directories(${PROJECT_SOURCE_DIR}/submodules/TEngine-Shader/include)
include_directories(${PROJECT_SOURCE_DIR}/submodules/TEngine-Window/include)

add_executable( ${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.c )

target_link_libraries( ${PROJECT_NAME} PRIVATE m tengine-camera tengine-shader tengine-window)