#include "display.h"
//#include "keyboard.h"
#include <stdio.h>

const int scale = 10;

//uint8_t display[DISPLAY_COLUMNS][DISPLAY_ROWS];
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
    sfRenderWindow_setFramerateLimit(window, 60);

    image = sfImage_createFromColor(DISPLAY_COLUMNS, DISPLAY_ROWS, sfBlack);
    texture = sfTexture_createFromImage(image, &rect);

    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, 0);
    sfVector2f scale = {10, 10};
    sfSprite_setScale(sprite, scale);

    sfRenderWindow_drawSprite(window, sprite, NULL);

//    for (int column = 0; column < DISPLAY_COLUMNS; column++)
//    {
//        for (int row = 0; row < DISPLAY_ROWS; row++)
//        {
//            pixels[column][row] = sfRectangleShape_create();
//            sfRectangleShape_setPosition(pixels[column][row], (sfVector2f) {column*scale, row*scale});
//            sfRectangleShape_setSize(pixels[column][row], (sfVector2f) {scale, scale});
//            sfRectangleShape_setOutlineColor(pixels[column][row], sfBlack);
//            sfRectangleShape_setFillColor(pixels[column][row], sfBlack);
//        }
//    }

    return window;
}

void drawPixel(int x, int y)
{
    x = x % DISPLAY_COLUMNS, y = y % DISPLAY_ROWS;

//    sfRectangleShape* pixel = sfRectangleShape_create();


    sfRenderWindow_drawRectangleShape(window, pixels[x][y], NULL);
}

void renderDisplay()
{
//    for (int column = 0; column < DISPLAY_COLUMNS; column++)
//    {
//        for (int row = 0; row < DISPLAY_ROWS; row++)
//        {
//            if (display[column][row])
//                drawPixel(column, row);
//        }
//    }
    sfTexture_updateFromPixels(texture, display, DISPLAY_COLUMNS, DISPLAY_ROWS, 0, 0);
    sfRenderWindow_drawSprite(window, sprite, NULL);
}

void displayClear()
{
    for (int column = 0; column < DISPLAY_COLUMNS; column++)
    {
        for (int row = 0; row < DISPLAY_ROWS; row++)
        {
            display[column * (32 + row)] = 0;
        }
    }
}
