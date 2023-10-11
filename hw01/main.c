#include "graphics.h"
#include "life.h"

enum {
    K_WIDTH = 100,
    K_HEIGHT = 50,
    K_CELL_SIZE = 10,
    K_FRAMERATE_LIMIT = 2,
    K_DENSITY = 4,
};

void display_gen(sfRenderWindow *window, State *gen, int width, int height) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            sfVector2f size = {K_CELL_SIZE, K_CELL_SIZE};
            sfVector2f position = {K_CELL_SIZE * x, K_CELL_SIZE * y};
            put_pixel(
                window, size, position,
                gen[x * height + y] == K_ALIVE ? sfCyan : sfBlack
            );
        }
    }
    flush(window);
}

int main() {
    int width = K_WIDTH;
    int height = K_HEIGHT;

    State curr_field_buffer[width * height];
    State next_field_buffer[width * height];

    State *curr_gen = curr_field_buffer;
    State *next_gen = next_field_buffer;

    init_gen(curr_gen, width, height, K_DENSITY);

    sfVideoMode mode = {
        width * K_CELL_SIZE, height * K_CELL_SIZE, sizeof(sfColor)};
    sfRenderWindow *window =
        sfRenderWindow_create(mode, "Game of Life", sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, K_FRAMERATE_LIMIT);
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                goto cleanup;
            }
        }

        calc_next_gen(curr_gen, next_gen, width, height);
        display_gen(window, curr_gen, width, height);

        State *temp = curr_gen;
        curr_gen = next_gen;
        next_gen = temp;
    }

cleanup:
    sfRenderWindow_close(window);
    sfRenderWindow_destroy(window);
}
