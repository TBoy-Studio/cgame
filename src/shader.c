#include <shader.h>

static Shader _compileShader(const char* shaderPath, GLenum type, Shader_Program program)
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
    char *shaderSrc = calloc(shaderFileSize + 1, sizeof(char));
    const char *shaderSrcPtr = (const char*)shaderSrc;

    // Read the file into the buffer
    unsigned long shaderBytesRead;
    shaderBytesRead = fread(shaderSrc, sizeof(char), shaderFileSize, shaderFile);
    if(shaderBytesRead != shaderFileSize) return 0; // Something went wrong while reading

    // Create GL shader
    Shader shader;
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

Shader_Program Shader_createProgram(const char* vertexPath, const char* geometryPath, const char* fragmentPath)
{
    // Create shader program
    Shader_Program program;
    program = glCreateProgram();

    // Compile shaders into program
    Shader vertex = _compileShader(vertexPath, GL_VERTEX_SHADER, program);
    Shader geometry = _compileShader(geometryPath, GL_GEOMETRY_SHADER, program);
    Shader fragment = _compileShader(fragmentPath, GL_FRAGMENT_SHADER, program);

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

void Shader_useProgram(Shader_Program program)
{
    glUseProgram(program);
}

void Shader_setBool(Shader_Program program, const char* name, unsigned char value)
{
    glUniform1i(glGetUniformLocation(program, name), (int)value);
}

void Shader_setInt(Shader_Program program, const char* name, int value)
{
    glUniform1i(glGetUniformLocation(program, name), value);
}

void Shader_setFloat(Shader_Program program, const char* name, float value)
{
    glUniform1f(glGetUniformLocation(program, name), value);
}

void Shader_setVec3(Shader_Program program, const char* name, vec3 value)
{
    glUniform3fv(glGetUniformLocation(program, name), 1, value);
}

void Shader_setMat4(Shader_Program program, const char* name, mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, &value[0][0]);
}
