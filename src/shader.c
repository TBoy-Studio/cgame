#include <shader.h>

unsigned int compile_shader(const char* vertex_src, const char* fragment_src){
    // Declare vars
    unsigned int vertex_shader, fragment_shader;
    int success;

    // First vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (const char**)&vertex_src, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    
    if(!success){
        return 0;
    }

    // Then fragment Shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (const char**)&fragment_src, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if(!success){
        return 0;
    }

    // Create program
    Shader program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // Check for linking errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        return 0;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

Shader shader_create(const char* vertex_path, const char* fragment_path){
    Shader shader;

    FILE* vertex_file = fopen(vertex_path, "r");
    FILE* fragment_file = fopen(fragment_path, "r");

    // Check if opening files was succesful
    if (vertex_file == NULL) {
        return 0;
    }
    if (fragment_file == NULL) {
        return 0;
    }

    // Get the length of the files
    fseek(vertex_file, 0L, SEEK_END);
    unsigned long vertex_file_length = ftell(vertex_file);
    rewind(vertex_file);
    fseek(fragment_file, 0L, SEEK_END);    
    unsigned long fragment_file_length = ftell(fragment_file);    
    rewind(fragment_file);

    // Create buffers to store file contents
    char vertex_src[vertex_file_length + 1];
    char fragment_src[fragment_file_length + 1];

    // Add terminating zeroes to buffers
    vertex_src[vertex_file_length] = '\0';
    fragment_src[fragment_file_length] = '\0';

    // Read from files into buffers
    unsigned long vertex_bytes_read = fread(vertex_src, sizeof(char), vertex_file_length, vertex_file);
    unsigned long fragment_bytes_read = fread(fragment_src, sizeof(char), fragment_file_length, fragment_file);

    // Check if read was succesful
    if(vertex_bytes_read != vertex_file_length){
        return 0;
    }
    if(fragment_bytes_read != fragment_file_length){
        return 0;
    }

    // Try and compile shaders
    shader = compile_shader(vertex_src, fragment_src);

    return shader;
}

void shader_use(Shader shader){
    glUseProgram(shader);
}

void shader_set_bool(Shader shader, const char* name, unsigned char value){
    glUniform1i(glGetUniformLocation(shader, name), (int)value);
}

void shader_set_int(Shader shader, const char* name, int value){
    glUniform1i(glGetUniformLocation(shader, name), value);
}

void shader_set_float(Shader shader, const char* name, float value){
    glUniform1f(glGetUniformLocation(shader, name), value);
}

void shader_set_vec3(Shader shader, const char* name, vec3 value){
    glUniform3fv(glGetUniformLocation(shader, name), 1, value);
}

void shader_set_mat4(Shader shader, const char* name, mat4 value){
    glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, &value[0][0]);
}
