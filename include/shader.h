#ifndef SHADER_H
#define SHADER_H

// 3rd Party Libraries
#include <glad/gl.h>
#include <cglm/types.h>

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>

/*
    A shader is actually just an unsigned integer.
    This typedef makes it easier to distinguish between Shader and Shader_Program.
*/
typedef unsigned int CGameShader;

/*
    A shader program is actually just an unsigned integer.
    This typedef makes it easier to distinguish between Shader_Program and Shader.
*/
typedef unsigned int CGameShaderProgram;

/*
    Creates an OpenGL shader program build from the source files specified in the arguments.
    If a geometry shader is not needed, you can just pass a NULL pointer to the geometryPath.
    Vertex and Fragment shaders are always required for a shader program.
*/
CGameShaderProgram cgame_shader_create_program(const char* vertexPath, const char* geometryPath, const char* fragmentPath);

/*
    Tells OpenGL to start using this program for drawing
*/
void cgame_shader_use_program(CGameShaderProgram program);

/*
    Simply sets a uniform bool in a shader program specified by it's name
*/
void cgame_shader_set_bool(CGameShaderProgram program, const char* name, unsigned char value);

/*
    Simply sets a uniform int in a shader program specified by it's name
*/
void cgame_shader_set_int(CGameShaderProgram program, const char* name, int value);

/*
    Simply sets a uniform float in a shader program specified by it's name
*/
void cgame_shader_set_float(CGameShaderProgram program, const char* name, float value);

/*
    Simply sets a uniform vec3 in a shader program specified by it's name
*/
void cgame_shader_set_vec3(CGameShaderProgram program, const char* name, vec3 value);

/*
    Simply sets a uniform mat4 in a shader program specified by it's name
*/
void cgame_shader_set_mat4(CGameShaderProgram program, const char* name, mat4 value);

#endif
