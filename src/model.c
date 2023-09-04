#include <model.h>

static void setupMesh(Model_Mesh* mesh){
    // Make buffer objects and vertex arrays
    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);

    glBindVertexArray(mesh->vao);

    // Set vertex buffer data
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertex_count * sizeof(Model_Vertex), mesh->vertices, GL_STATIC_DRAW);

    // Set vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Model_Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Model_Vertex), (void*)offsetof(Model_Vertex, normal));

    glBindVertexArray(0);
}

void Model_createMesh(Model_Vertex* vertices, unsigned int vertex_count, Model_Mesh* result){
    // Assign values
    result->vertices = vertices;
    result->vertex_count = vertex_count;

    // Setup mesh for drawing with OpenGL
    setupMesh(result);
    return;
}

void Model_drawMesh(Model_Mesh* mesh){    
    glBindVertexArray(mesh->vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_count);
    glBindVertexArray(0);
}
