cmake_minimum_required(VERSION 3.10)

project(cgame VERSION 1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Used by clang language server for code completion
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# Build as static lib
set(BUILD_SHARED_LIBS False)

# GLFW Options
set(GLFW_BUILD_EXAMPLES False)
set(GLFW_BUILD_TESTS False)
set(GLFW_BUILD_DOCS False)
set(GLFW_INSTALL False)

# Include directories for header files
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/deps/glfw/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/deps/glfw)

add_library( ${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/deps/cJSON/cJSON.c
    ${PROJECT_SOURCE_DIR}/src/gl.c
    ${PROJECT_SOURCE_DIR}/src/file.c
    ${PROJECT_SOURCE_DIR}/src/shader.c
    ${PROJECT_SOURCE_DIR}/src/camera.c
    ${PROJECT_SOURCE_DIR}/src/window.c
    ${PROJECT_SOURCE_DIR}/src/input.c
    ${PROJECT_SOURCE_DIR}/src/model.c
    ${PROJECT_SOURCE_DIR}/src/components/components.c
    ${PROJECT_SOURCE_DIR}/src/components/controller.c
    ${PROJECT_SOURCE_DIR}/src/components/meshrenderer.c
    ${PROJECT_SOURCE_DIR}/src/components/rigidbody.c
    ${PROJECT_SOURCE_DIR}/src/components/transform.c
    ${PROJECT_SOURCE_DIR}/src/scene.c
    ${PROJECT_SOURCE_DIR}/src/memory.c
    ${PROJECT_SOURCE_DIR}/src/physics.c
    ${PROJECT_SOURCE_DIR}/src/cgame.c
)

add_subdirectory(${PROJECT_SOURCE_DIR}/test)

if(WIN32)
    target_link_libraries( ${PROJECT_NAME} PRIVATE glfw )
else()
    target_link_libraries( ${PROJECT_NAME} PRIVATE m glfw )
endif()