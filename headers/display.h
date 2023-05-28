#include <stdint.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#ifndef DISPLAY_H
#define DISPLAY_H

#define DISPLAY_COLUMNS 64
#define DISPLAY_ROWS 32

extern sfUint8 display[DISPLAY_COLUMNS * DISPLAY_ROWS * 4];

void displayClear();
sfRenderWindow * init_display(void);
void drawPixel(int x, int y);
void renderDisplay();

#endif // DISPLAY_H
