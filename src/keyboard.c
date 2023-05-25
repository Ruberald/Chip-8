#include <keyboard.h>

int keyboard[16];

void handle_keyboard_input(int keyCode, int flag)
{
    switch(keyCode)
    {
    case sfKeyNum0:
        keyboard[0] = flag;
        break;
    case sfKeyNum1:
        keyboard[1] = flag;
        break;
    case sfKeyNum2:
        keyboard[2] = flag;
        break;
    case sfKeyNum3:
        keyboard[3] = flag;
        break;
    case sfKeyNum4:
        keyboard[4] = flag;
        break;
    case sfKeyNum5:
        keyboard[5] = flag;
        break;
    case sfKeyNum6:
        keyboard[6] = flag;
        break;
    case sfKeyNum7:
        keyboard[7] = flag;
        break;
    case sfKeyNum8:
        keyboard[8] = flag;
        break;
    case sfKeyNum9:
        keyboard[9] = flag;
        break;
    case sfKeyA:
        keyboard[10] = flag;
        break;
    case sfKeyB:
        keyboard[11] = flag;
        break;
    case sfKeyC:
        keyboard[12] = flag;
        break;
    case sfKeyD:
        keyboard[13] = flag;
        break;
    case sfKeyE:
        keyboard[14] = flag;
        break;
    case sfKeyF:
        keyboard[15] = flag;
        break;

    }
}
