#ifndef MODEL_H
#define MODEL_H

#include <cglm/vec3.h>
#include <glad/gl.h>

typedef struct{
    vec3 position;
    vec3 normal;
} Vertex;

typedef unsigned int Index;

typedef struct{
    Vertex* vertices;
    unsigned int vertex_count;
    unsigned int vao, vbo;
} Mesh;

void mesh_create(Vertex* vertices, unsigned int vertex_count, Mesh* result);
void mesh_draw(Mesh* mesh);

#endif
