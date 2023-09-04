#ifndef MODEL_H
#define MODEL_H

#include <cglm/vec3.h>
#include <glad/gl.h>

/*
    Simple struct to hold info per vertex
*/
typedef struct{
    vec3 position;
    vec3 normal;
} Model_Vertex;

/*
    The mesh holds the vertices array and a vao and vbo for drawing the mesh
*/
typedef struct{
    Model_Vertex* vertices;
    unsigned int vertex_count;
    unsigned int vao, vbo;
} Model_Mesh;

/*
    Build a mesh out of an array of vertices
*/
void Model_createMesh(Model_Vertex* vertices, unsigned int vertex_count, Model_Mesh* result);

/*
    Executes a draw call to draw the specified mesh
*/
void Model_drawMesh(Model_Mesh* mesh);

#endif
