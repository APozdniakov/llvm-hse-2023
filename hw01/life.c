#include "life.h"
#include <stdlib.h>
#include "sim.h"

enum {
    K_DENSITY = 4,
};

typedef enum State { K_DEAD = 0, K_ALIVE = 1 } State;

static void init_gen(State *gen, int width, int height, int density) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            gen[x * height + y] = sim_rand() % density ? K_DEAD : K_ALIVE;
        }
    }
}

static void
calc_next_gen(State *curr_gen, State *next_gen, int width, int height) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int alive = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int new_x = x + dx;
                    int new_y = y + dy;
                    if (abs(dx) + abs(dy) == 1 && 0 <= new_x && new_x < width &&
                        0 <= new_y && new_y < height &&
                        curr_gen[new_x * height + new_y] == K_ALIVE) {
                        alive += 1;
                    }
                }
            }

            next_gen[x * height + y] =
                curr_gen[x * height + y] == K_DEAD && alive != 3 ||
                        curr_gen[x * height + y] == K_ALIVE && alive != 2 &&
                            alive != 3
                    ? K_DEAD
                    : K_ALIVE;
        }
    }
}

static void display_gen(State *gen, int width, int height) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            sim_set_pixel(x, y, gen[x * height + y] == K_ALIVE);
        }
    }
    sim_flush();
}

void app(void) {
    State curr_gen_buffer[K_WIDTH * K_HEIGHT];
    State next_gen_buffer[K_WIDTH * K_HEIGHT];

    State *curr_gen = curr_gen_buffer;
    State *next_gen = next_gen_buffer;

    init_gen(curr_gen, K_WIDTH, K_HEIGHT, K_DENSITY);

    while (sim_keep_running()) {
        calc_next_gen(curr_gen, next_gen, K_WIDTH, K_HEIGHT);

        display_gen(curr_gen, K_WIDTH, K_HEIGHT);

        State *temp = curr_gen;
        curr_gen = next_gen;
        next_gen = temp;
    }
}
