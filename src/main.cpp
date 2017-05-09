

#include <cstdio>
#include <cinttypes>

#include "shader.hpp"
#include "renderer.hpp"

//Config variables
const bool draw_anchors = false;
const int border = 1;
const int grid_res = 16;

struct v2 {
    int x;
    int y;
};

struct tetromino{
    //shape
    v2 loc[4];
    color c;
};

tetromino tetromino_types[] = {
    {{{0, 0}, {0, 1}, {0, 2}, {0, 3}}, cyan},
    {{{0, 0}, {0, 1}, {1, 0}, {0, 2}}, blue},
    {{{0, 0}, {1, 0}, {1, 1}, {1, 2}}, orange},
    {{{0, 0}, {0, 1}, {0, 2}, {1, 1}}, purple},
    {{{0, 0}, {1, 0}, {1, 1}, {2, 1}}, red},
    {{{0, 1}, {1, 1}, {1, 0}, {2, 0}}, green},
    {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}, yellow}
};


void fill_grid_square(Renderer& r, int x, int y, color c){
    r.drawSquare(x * grid_res + border, y * grid_res + border, grid_res - 2 * border, grid_res - 2 * border, c);
}

void draw_tetromino(Renderer& r, tetromino t, int rotation, int x, int y){
    switch (rotation) {
        case 0: for(auto i : t.loc) fill_grid_square(r, x + i.x, y + i.y, t.c); break;
        case 1: for(auto i : t.loc) fill_grid_square(r, x + i.y, y - i.x, t.c); break;
        case 2: for(auto i : t.loc) fill_grid_square(r, x - i.x, y - i.y, t.c); break;
        case 3: for(auto i : t.loc) fill_grid_square(r, x - i.y, y + i.x, t.c); break;
    }

    if (draw_anchors) fill_grid_square(r, x, y, white);
}


int main() {
    Renderer renderer;
    renderer.init();

    while(!glfwWindowShouldClose(renderer.window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        int x_loc = 5;
        for (auto t : tetromino_types) {
            draw_tetromino(renderer, t, 0, x_loc, 5);
            draw_tetromino(renderer, t, 1, x_loc, 10);
            draw_tetromino(renderer, t, 2, x_loc, 15);
            draw_tetromino(renderer, t, 3, x_loc, 20);
            
            x_loc += 5;
        }

        glfwSwapBuffers(renderer.window);
        glfwPollEvents();

    }
}
