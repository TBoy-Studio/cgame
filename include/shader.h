#ifndef SHADER_H
#define SHADER_H

// 3rd Party Libraries
#include <glad/gl.h>
#include <cglm/types.h>

// Standard Libraries
#include <stdio.h>

/*
    A shader is actually just an unsigned integer.
    This typedef makes it easier to distinguish between Shader and Shader_Program.
*/
typedef unsigned int Shader;

/*
    A shader program is actually just an unsigned integer.
    This typedef makes it easier to distinguish between Shader_Program and Shader.
*/
typedef unsigned int Shader_Program;

/*
    Creates an OpenGL shader program build from the source files specified in the arguments.
    If a geometry shader is not needed, you can just pass a NULL pointer to the geometryPath.
    Vertex and Fragment shaders are always required for a shader program.
*/
Shader_Program Shader_createProgram(const char* vertexPath, const char* geometryPath, const char* fragmentPath);

/*
    Tells OpenGL to start using this program for drawing
*/
void Shader_useProgram(Shader_Program program);

/*
    Simply sets a uniform bool in a shader program specified by it's name
*/
void Shader_setBool(Shader_Program program, const char* name, unsigned char value);

/*
    Simply sets a uniform int in a shader program specified by it's name
*/
void Shader_setInt(Shader_Program program, const char* name, int value);

/*
    Simply sets a uniform float in a shader program specified by it's name
*/
void Shader_setFloat(Shader_Program program, const char* name, float value);

/*
    Simply sets a uniform vec3 in a shader program specified by it's name
*/
void Shader_setVec3(Shader_Program program, const char* name, vec3 value);

/*
    Simply sets a uniform mat4 in a shader program specified by it's name
*/
void Shader_setMat4(Shader_Program program, const char* name, mat4 value);

#endif
