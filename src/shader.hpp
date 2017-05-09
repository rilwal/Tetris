#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>
#include <cinttypes>


class Shader {
    public:
        enum Type {
            Compute = GL_COMPUTE_SHADER,
            Vertex = GL_VERTEX_SHADER,
            Tess_Control = GL_TESS_CONTROL_SHADER,
            Tess_Eval = GL_TESS_EVALUATION_SHADER,
            Geometry = GL_GEOMETRY_SHADER,
            Fragment = GL_FRAGMENT_SHADER
        };

    private:
        std::string source;
        uint32_t shader_id;

    public:
        Shader(Type shaderType, std::string filename);
        ~Shader();

        bool compiled;
        bool is_active();
        void use(); 

        friend class Program; // needs to access shader_id
};


class Program {
    private:
        uint32_t program_id;
        std::vector<Shader> shaders;

    public:
        Program();
        ~Program();

        void attach(Shader shader);
        bool link();
        void use();

        uint32_t get_id() {return program_id;}

        bool is_linked;
};

