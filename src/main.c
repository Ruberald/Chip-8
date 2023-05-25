//#include "display.h"
#include "cpu.h"
#include "memory.h"
#include "keyboard.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct memory * mem;
    printf("%s", argv[1]);
    mem = init_mem(argv[1]);

    reset();

    struct central_processing_unit * cpu = set_memory(mem);

    uint16_t opcode;

    sfRenderWindow * window = init_display();

    sfEvent event;

    while (sfRenderWindow_isOpen(window))
    {
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtKeyPressed)
                handle_keyboard_input(event.key.code, 1);
            else if (event.type == sfEvtKeyReleased)
                handle_keyboard_input(event.key.code, 0);
        }
        sfRenderWindow_clear(window, sfBlack);

        renderDisplay();

        sfRenderWindow_display(window);

        opcode = (mem->data[cpu->pc] << 8u) | (mem->data[cpu->pc + 1]);
        cpu->pc += 2;

        switch(opcode & 0xF000)
        {
        case 0x0000:
            switch(opcode)
            {
            case 0x00E0:
                CLS_00E0();
                break;
            case 0x00EE:
                RET_00EE();
                break;
            }
            break;

        case 0x1000:
            JP_1nnn(opcode & 0x0FFF);
            break;

        case 0x6000:
            LD_6xkk((opcode & 0x0F00) >> 8, (opcode & 0x00FF));
            break;

        case 0x7000:
            ADD_7xkk((opcode & 0x0F00) >> 8, (opcode & 0x00FF));
            break;

        case 0xA000:
            LD_Annn((opcode & 0x0FFF));
            break;

        case 0xD000:
            DRW_Dxyn((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4, (opcode & 0x000F));
            break;
        }
    }

    sfRenderWindow_destroy(window);

    return 0;
}
