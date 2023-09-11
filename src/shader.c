#include <shader.h>

static CGameShader _compile_shader(const char* shaderPath, GLenum type, CGameShaderProgram program)
{
    // Sanity check
    if(!shaderPath) return 0;

    // Try opening file
    FILE* shaderFile = fopen(shaderPath, "r"); 
    if(!shaderFile) return 0;

    // Get shader file size
    unsigned long shaderFileSize;    
    fseek(shaderFile, 0, SEEK_END);
    shaderFileSize = ftell(shaderFile);
    rewind(shaderFile);

    // Setup buffer for file contents
    char shaderSrc[shaderFileSize + 1];
    const char *shaderSrcPtr = (const char*)shaderSrc;
    shaderSrc[shaderFileSize] = '\0';

    // Read the file into the buffer
    unsigned long shaderBytesRead;
    shaderBytesRead = fread(shaderSrc, sizeof(char), shaderFileSize, shaderFile);
    if(shaderBytesRead != shaderFileSize) return 0; // Something went wrong while reading

    // Create GL shader
    CGameShader shader;
    int success;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const char**)&shaderSrcPtr, NULL);

    // Compile shader
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) return 0;

    // Attach shader to program
    glAttachShader(program, shader);

    // Return the shader so it can later be erased after linking
    return shader;
}

CGameShaderProgram cgame_shader_create_program(const char* vertexPath, const char* geometryPath, const char* fragmentPath)
{
    // Create shader program
    CGameShaderProgram program;
    program = glCreateProgram();

    // Compile shaders into program
    CGameShader vertex = _compile_shader(vertexPath, GL_VERTEX_SHADER, program);
    CGameShader geometry = _compile_shader(geometryPath, GL_GEOMETRY_SHADER, program);
    CGameShader fragment = _compile_shader(fragmentPath, GL_FRAGMENT_SHADER, program);

    // Link program
    int success;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glDeleteProgram(program);
        program = 0;
    }

    // Delete shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);

    return program;
}

void cgame_shader_use_program(CGameShaderProgram program)
{
    glUseProgram(program);
}

void cgame_shader_set_bool(CGameShaderProgram program, const char* name, unsigned char value)
{
    glUniform1i(glGetUniformLocation(program, name), (int)value);
}

void cgame_shader_set_int(CGameShaderProgram program, const char* name, int value)
{
    glUniform1i(glGetUniformLocation(program, name), value);
}

void cgame_shader_set_float(CGameShaderProgram program, const char* name, float value)
{
    glUniform1f(glGetUniformLocation(program, name), value);
}

void cgame_shader_set_vec3(CGameShaderProgram program, const char* name, vec3 value)
{
    glUniform3fv(glGetUniformLocation(program, name), 1, value);
}

void cgame_shader_set_mat4(CGameShaderProgram program, const char* name, mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0]);
}
