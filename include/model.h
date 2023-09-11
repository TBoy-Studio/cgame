#pragma once

#include <cglm/vec3.h>
#include <glad/gl.h>

/*
    Simple struct to hold info per vertex
*/
typedef struct{
    vec3 position;
    vec3 normal;
} CGameModelVertex;

/*
    The mesh holds the vertices array and a vao and vbo for drawing the mesh
*/
typedef struct{
    CGameModelVertex* vertices;
    unsigned int vertex_count;
    unsigned int vao, vbo;
} CGameModelMesh;

/*
    Build a mesh out of an array of vertices
*/
void cgame_model_create_mesh(CGameModelVertex* vertices, unsigned int vertex_count, CGameModelMesh* result);

/*
    Executes a draw call to draw the specified mesh
*/
void cgame_model_draw_mesh(CGameModelMesh* mesh);
