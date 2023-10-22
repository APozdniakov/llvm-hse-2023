#pragma once

enum {
    K_WIDTH = 100,
    K_HEIGHT = 50,
};

int sim_keep_running(void);

void sim_set_pixel(int x, int y, int state);

void sim_flush(void);

int sim_rand(void);
