#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SFML/Window/Keyboard.h>

extern int keyboard[16];

void handle_keyboard_input(int keyCode, int flag);

#endif // KEYBOARD_H
