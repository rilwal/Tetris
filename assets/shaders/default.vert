#version 330 core

in vec2 vertexPosition_screenspace;
in vec3 color_in;

out vec3 color;

uniform int width;
uniform int height;

void main() {
    float x_scale = 2.0 / width;
    float y_scale = 2.0 / height;

    color = color_in;

    gl_Position.x = vertexPosition_screenspace.x * (2.0 / width) - 1.0;
    gl_Position.y = 1.0 - (vertexPosition_screenspace.y * (2.0 / height));
    gl_Position.z = 1.0;
    gl_Position.w = 1.0;
}

