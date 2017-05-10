
#include "renderer.hpp"
#include <cinttypes>
#include <GL/glew.h>
#include "shader.hpp"


bool Renderer::init() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return false;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "games", 0, 0);

    if (window == nullptr) {
        fprintf(stderr, "Failed to open window\n");
        return false;
    }


    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return false;
    }

    default_shaders = new Program();
    default_shaders->attach(Shader(Shader::Type::Vertex,   "assets/shaders/default.vert"));
    default_shaders->attach(Shader(Shader::Type::Fragment, "assets/shaders/default.frag"));

    default_shaders->link();

    int uniform_window_width  = glGetUniformLocation(default_shaders->get_id(), "width");
    int uniform_window_height = glGetUniformLocation(default_shaders->get_id(), "height");

    default_shaders->use();
    glUniform1i(uniform_window_width,  width);
    glUniform1i(uniform_window_height, height);

    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    glGenBuffers(1, &vertex_buffer_id);
    glGenBuffers(1, &color_buffer_id); 

    return true;
}

void Renderer::drawSquare(float x, float y, float w, float h, color c) {
    //
    // x,y----x2,y
    // |        |
    // |        |
    // |        |
    // |        |
    // x,y2---x2,y2
    //
    
    static bool initialized = false;

    if (!initialized) {
        initialized = true;
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void*)0);

    }

    float x2 = x + w;
    float y2 = y + h;

    float vertex_buffer[] = {
        x,  y,
        x,  y2,
        x2, y,
        x2, y,
        x,  y2,
        x2, y2
    };

    float r = c.r / 255.f;
    float g = c.g / 255.f;
    float b = c.b / 255.f;

    int uniform_color = glGetUniformLocation(default_shaders->get_id(), "color");
    glUniform3f(uniform_color, r, g, b);

    glNamedBufferData(vertex_buffer_id, sizeof(vertex_buffer), vertex_buffer, GL_STREAM_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

