#pragma once

#include "SFML/Graphics.h"
#include "life.h"

static inline void put_pixel(
    sfRenderWindow *window,
    sfVector2f size,
    sfVector2f position,
    sfColor color
) {
    sfRectangleShape *shape = sfRectangleShape_create();
    sfRectangleShape_setSize(shape, size);
    sfRectangleShape_setPosition(shape, position);
    sfRectangleShape_setFillColor(shape, color);
    sfRenderWindow_drawRectangleShape(window, shape, NULL);
    sfRectangleShape_destroy(shape);
}

static inline void flush(sfRenderWindow *window) {
    sfRenderWindow_display(window);
}
