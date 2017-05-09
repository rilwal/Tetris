
#include <iostream>
#include <fstream>

#include "shader.hpp"


//TODO:
// * Make shaders compile
// * Implement Shader::use()
// * Implement Shader::is_active();

Shader::Shader(Shader::Type type, std::string filename) {
    shader_id = glCreateShader(type);
    std::ifstream file(filename, std::ios::ate);
    

    if(file.is_open()) {
        std::streampos size = file.tellg();
        source.resize(size);
        
        file.seekg(0, std::ios::beg);
        file.read(&source[0], size);
        file.close();

        char* source_ptr = &source[0];
        glShaderSource(shader_id, 1, &source_ptr, NULL);
        glCompileShader(shader_id);
        
        GLint success;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

        if (success == GL_TRUE) compiled = true;
        else {
            //TODO: report errors
            compiled = false;

            GLsizei log_length = 0;
            GLchar message[1024];
            glGetShaderInfoLog(shader_id, 1024, &log_length, message);

            std::cerr << message;

        }
    }
}

Shader::~Shader () {
    glDeleteShader(shader_id);
}

Program::Program() {
    program_id = glCreateProgram();
}

Program::~Program() {
    glDeleteProgram(program_id);
}

void Program::attach(Shader shader) {
    if (shader.compiled) {
        shaders.push_back(shader);
        glAttachShader(program_id, shader.shader_id);
    } else std::cerr << "Could not attach shader: shader not compiled\n";
}

bool Program::link() {
    glLinkProgram(program_id);

    int32_t success;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);

    if(success == GL_TRUE) is_linked = true;
    else {
        //TODO: Errors
        is_linked = false;
    }

    return is_linked;
}

void Program::use() {
    glUseProgram(program_id);
}
