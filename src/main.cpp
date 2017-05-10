

#include <cstdio>
#include <cinttypes>

#include "shader.hpp"
#include "renderer.hpp"

//Config variables
const bool draw_anchors = false;
const bool draw_background = false;
const int border = 1;
const int grid_res = 16;

struct v2 {
    int x;
    int y;
};

struct tetromino {
    v2 geometry[4];
    int width;
    color c;
};


tetromino tetromino_types[] = {
    {{{0, 1}, {1, 1}, {2, 1}, {3, 1}}, 4, cyan},
    {{{0, 1}, {1, 1}, {0, 0}, {2, 1}}, 3, blue},
    {{{0, 1}, {1, 1}, {2, 1}, {2, 0}}, 3, orange},
    {{{0, 1}, {1, 1}, {1, 0}, {2, 1}}, 3, purple},
    {{{0, 0}, {1, 0}, {1, 1}, {2, 1}}, 3, red},
    {{{0, 1}, {1, 1}, {1, 0}, {2, 0}}, 3, green},
    {{{0, 0}, {1, 0}, {1, 1}, {0, 1}}, 2, yellow}
};


void fill_grid_square(Renderer& r, int x, int y, color c){
    r.drawSquare(x * grid_res + border, y * grid_res + border, grid_res - 2 * border, grid_res - 2 * border, c);
}

void draw_tetromino(Renderer& r, tetromino t, int rotation, int x, int y){
    // Rotation system based loosly on SRS
    // http://tetris.wikia.com/wiki/SRS
    
    int offset = (t.width + 1) / 2;

    if (t.width == 4) {
        offset = t.width / 2 + 1;
    }

    if (draw_background) {
        for (int bgx = 0; bgx < t.width; bgx++) {
            for (int bgy = 0; bgy < t.width; bgy++) {
                fill_grid_square(r, x - offset + bgx, y - offset + bgy, white);
            }
        }
    }

    for (auto i : t.geometry) {
        int tx = (i.x - offset);
        int ty = (i.y - offset);

        switch (rotation) {
            case 0: fill_grid_square(r, x + tx, y + ty, t.c); break;
            case 1: fill_grid_square(r, x - ty - offset, y + tx, t.c); break;
            case 2: fill_grid_square(r, x - tx - offset, y - ty - offset, t.c); break;
            case 3: fill_grid_square(r, x + ty, y - tx - offset, t.c); break;
            default: fprintf(stderr, "Invalid tetromino rotation\n");
        }
    }

    if (draw_anchors) fill_grid_square(r, x - 1, y - 1, green);
}


int main() {
    Renderer renderer;
    if(!renderer.init()) {
        fprintf(stderr, "Failed to initialize renderer, exiting");
        return -1;
    }


    while(!glfwWindowShouldClose(renderer.window)) {

       glClear(GL_COLOR_BUFFER_BIT);
        
        int y_loc = 5;
        for (auto t : tetromino_types) {
            draw_tetromino(renderer, t, 0,  5, y_loc);
            draw_tetromino(renderer, t, 1, 10, y_loc);
            draw_tetromino(renderer, t, 2, 15, y_loc);
            draw_tetromino(renderer, t, 3, 20, y_loc);
            
            y_loc += 5;
        }

        glfwSwapBuffers(renderer.window);
        glfwPollEvents();

    }

    return 0;
}
