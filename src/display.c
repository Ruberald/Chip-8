#include "display.h"
//#include "keyboard.h"
#include <stdio.h>

const int scale = 10;

uint8_t display[DISPLAY_COLUMNS][DISPLAY_ROWS];

sfRenderWindow* window;
sfVideoMode mode = {DISPLAY_COLUMNS*scale, DISPLAY_ROWS*scale, 32};

sfRenderWindow * init_display(void)
{
    displayClear();

    window = sfRenderWindow_create(mode, "Chip-8 emu", sfResize | sfClose, NULL);
    if (!window) return window;
    sfRenderWindow_setFramerateLimit(window, 60);
    
    return window;
}

void drawPixel(int x, int y)
{
    x = x % DISPLAY_COLUMNS, y = y % DISPLAY_ROWS;

    sfRectangleShape* pixel = sfRectangleShape_create();
    sfRectangleShape_setPosition(pixel, (sfVector2f) {x*scale, y*scale});
    sfRectangleShape_setSize(pixel, (sfVector2f) {scale, scale});

    sfRenderWindow_drawRectangleShape(window, pixel, NULL);
}

void renderDisplay()
{
    for (int column = 0; column < DISPLAY_COLUMNS; column++)
    {
        for (int row = 0; row < DISPLAY_ROWS; row++)
        {
            if (display[column][row])
                drawPixel(column, row);
        }
    }
}

void displayClear()
{
    for (int column = 0; column < DISPLAY_COLUMNS; column++)
    {
        for (int row = 0; row < DISPLAY_ROWS; row++)
        {
            display[column][row] = 0;
        }
    }
}
