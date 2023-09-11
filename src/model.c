#include <model.h>

static void _setup_mesh(CGameModelMesh* mesh)
{
    // Make buffer objects and vertex arrays
    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);

    glBindVertexArray(mesh->vao);

    // Set vertex buffer data
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertex_count * sizeof(CGameModelVertex), mesh->vertices, GL_STATIC_DRAW);

    // Set vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CGameModelVertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CGameModelVertex), (void*)offsetof(CGameModelVertex, normal));

    glBindVertexArray(0);
}

void cgame_model_create_mesh(CGameModelVertex* vertices, unsigned int vertex_count, CGameModelMesh* result)
{
    // Assign values
    result->vertices = vertices;
    result->vertex_count = vertex_count;

    // Setup mesh for drawing with OpenGL
    _setup_mesh(result);
    return;
}

void cgame_model_draw_mesh(CGameModelMesh* mesh)
{    
    glBindVertexArray(mesh->vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_count);
    glBindVertexArray(0);
}
