#include <model.h>

void mesh_setup(Mesh* mesh){
    // Make buffer objects and vertex arrays
    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);

    glBindVertexArray(mesh->vao);

    // Set vertex buffer data
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertex_count * sizeof(Vertex), mesh->vertices, GL_STATIC_DRAW);

    // Set vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glBindVertexArray(0);
}

void mesh_create(Vertex* vertices, unsigned int vertex_count, Mesh* result){
    result->vertices = vertices;
    result->vertex_count = vertex_count;

    mesh_setup(result);
    return;
}

void mesh_draw(Mesh* mesh){    
    glBindVertexArray(mesh->vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_count);
    glBindVertexArray(0);
}
