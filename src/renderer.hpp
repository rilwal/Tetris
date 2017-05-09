#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

constexpr int width = 800;
constexpr int height = 600;

struct color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

const color white  = {255, 255, 255};
const color black  = {  0,   0,   0};
const color red    = {255,   0,   0};
const color green  = {  0, 255,   0};
const color blue   = {  0,   0, 255};
const color yellow = {255, 255,   0};
const color orange = {255, 170,   0};
const color purple = {255,   0, 255};
const color cyan   = {  0, 255, 255};


struct Renderer {
    Program* default_shaders;
    GLFWwindow* window;

    uint32_t vertex_array_id;
    uint32_t vertex_buffer_id;
    uint32_t color_buffer_id;

    bool init();
    void drawSquare(float x, float y, float w, float h, color=white);
};

