#include "sim.h"
#include <SFML/Graphics.h>
#include <assert.h>
#include <stdlib.h>

enum {
    K_CELL_SIZE = 10,
    K_FRAMERATE_LIMIT = 2,
};

typedef sfRenderWindow *SimWindow;

static void sim_create_window(SimWindow *window) {
    sfVideoMode mode = {
        K_WIDTH * K_CELL_SIZE, K_HEIGHT * K_CELL_SIZE, sizeof(sfColor)};
    *window = sfRenderWindow_create(mode, "Game of Life", sfClose, NULL);
    sfRenderWindow_setFramerateLimit(*window, K_FRAMERATE_LIMIT);
}

static void sim_destroy_window(SimWindow *window) {
    sfRenderWindow_close(*window);
    sfRenderWindow_destroy(*window);
    window = NULL;
}

static SimWindow *sim_get_window(void) {
    static SimWindow window = NULL;
    if (window == NULL) {
        sim_create_window(&window);
    }
    return &window;
}

int sim_keep_running(void) {
    assert(*sim_get_window());
    int result = sfRenderWindow_isOpen(*sim_get_window());
    if (result) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(*sim_get_window(), &event)) {
            if (event.type == sfEvtClosed) {
                result = 0;
                break;
            }
        }
    }
    if (!result) {
        sim_destroy_window(sim_get_window());
    }
    return result;
}

void sim_set_pixel(int x, int y, int state) {
    assert(*sim_get_window());
    sfRectangleShape *shape = sfRectangleShape_create();
    sfVector2f size = {K_CELL_SIZE, K_CELL_SIZE};
    sfRectangleShape_setSize(shape, size);
    sfVector2f position = {K_CELL_SIZE * x, K_CELL_SIZE * y};
    sfRectangleShape_setPosition(shape, position);
    sfColor color = state ? sfCyan : sfBlack;
    sfRectangleShape_setFillColor(shape, color);
    sfRenderWindow_drawRectangleShape(*sim_get_window(), shape, NULL);
    sfRectangleShape_destroy(shape);
}

void sim_flush(void) {
    assert(*sim_get_window());
    sfRenderWindow_display(*sim_get_window());
}

int sim_rand(void) {
    return rand();
}
