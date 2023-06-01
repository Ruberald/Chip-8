#include <keyboard.h>

int keyboard[16];

void handle_keyboard_input(int keyCode, int flag)
{
    switch(keyCode)
    {
    case sfKeyX:
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
    case sfKeyQ:
        keyboard[4] = flag;
        break;
    case sfKeyW:
        keyboard[5] = flag;
        break;
    case sfKeyE:
        keyboard[6] = flag;
        break;
    case sfKeyA:
        keyboard[7] = flag;
        break;
    case sfKeyS:
        keyboard[8] = flag;
        break;
    case sfKeyD:
        keyboard[9] = flag;
        break;
    case sfKeyZ:
        keyboard[10] = flag;
        break;
    case sfKeyC:
        keyboard[11] = flag;
        break;
    case sfKeyNum4:
        keyboard[12] = flag;
        break;
    case sfKeyR:
        keyboard[13] = flag;
        break;
    case sfKeyF:
        keyboard[14] = flag;
        break;
    case sfKeyV:
        keyboard[15] = flag;
        break;

    }
}
