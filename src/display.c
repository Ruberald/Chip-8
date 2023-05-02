#include "display.h"

const int displayColumns = 64, displayRows = 32, scale = 10;

sfRenderWindow* window;
sfVideoMode mode = {displayColumns*scale, displayRows*scale, 32};

int init_display(void)
{
    window = sfRenderWindow_create(mode, "Chip-8 emu", sfResize | sfClose, NULL);
    if (!window) return EXIT_FAILURE;
    sfRenderWindow_setFramerateLimit(window, 60);

    sfEvent event;

    while (sfRenderWindow_isOpen(window))
    {
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        sfRenderWindow_clear(window, sfBlack);

        drawPixel(5, 5);
        drawPixel(5, 7);
        drawPixel(100, 70);

        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
    
    return EXIT_SUCCESS;
}

void drawPixel(int x, int y)
{
    x = x % displayColumns, y = y % displayRows;

    sfRectangleShape* pixel = sfRectangleShape_create();
    sfRectangleShape_setPosition(pixel, (sfVector2f) {x*scale, y*scale});
    sfRectangleShape_setSize(pixel, (sfVector2f) {scale, scale});

    sfRenderWindow_drawRectangleShape(window, pixel, NULL);
}
