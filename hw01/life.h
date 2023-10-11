#pragma once

#include <stdlib.h>
#include "life.h"

typedef enum State { K_DEAD = 0, K_ALIVE = 1 } State;

static inline void init_gen(State *gen, int width, int height, int density) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            gen[x * height + y] = rand() % density ? K_DEAD : K_ALIVE;
        }
    }
}

static inline void
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
