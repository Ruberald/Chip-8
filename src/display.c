#include "display.h"
#include <stdio.h>

const int scale = 10;

sfUint8 display[DISPLAY_COLUMNS * DISPLAY_ROWS * 4];

sfRectangleShape * pixels[DISPLAY_COLUMNS][DISPLAY_ROWS];

sfRenderWindow* window;
sfVideoMode mode = {DISPLAY_COLUMNS*scale, DISPLAY_ROWS*scale, 32};

sfImage * image;
sfTexture * texture;
sfSprite * sprite;

sfIntRect rect = {64, 32};

sfRenderWindow * init_display(void)
{
    displayClear();

    window = sfRenderWindow_create(mode, "Chip-8 emu", sfResize | sfClose, NULL);
    if (!window) return window;

    image = sfImage_createFromColor(DISPLAY_COLUMNS, DISPLAY_ROWS, sfBlack);
    texture = sfTexture_createFromImage(image, &rect);

    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, 0);
    sfVector2f scale = {10, 10};
    sfSprite_setScale(sprite, scale);

    sfRenderWindow_drawSprite(window, sprite, NULL);

    return window;
}

void renderDisplay()
{
    sfTexture_updateFromPixels(texture, display, DISPLAY_COLUMNS, DISPLAY_ROWS, 0, 0);
    sfRenderWindow_drawSprite(window, sprite, NULL);
}

void displayClear()
{
    for (int index = 0; index < (4 * DISPLAY_COLUMNS * DISPLAY_ROWS); index++)
    {
            display[index] = 0;
    }
}
