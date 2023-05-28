//#include "display.h"
#include "cpu.h"
#include "memory.h"
#include "keyboard.h"
#include <stdio.h>
#include <time.h>
#include <SFML/Audio.h>

int main(int argc, char *argv[])
{
    struct memory * mem;
//    printf("%s", argv[1]);
    mem = init_mem(argv[1]);

    reset();

    struct central_processing_unit * cpu = set_memory(mem);

    uint16_t opcode;

    sfRenderWindow * window = init_display();

    sfEvent event;

//    time_t time_last = time(NULL);

//    sfInt16 soundSamples[] = {0xFFFF};
//    sfSoundBuffer * buffer = sfSoundBuffer_createFromSamples(soundSamples, 1, 1, 44100);
//    sfSound * sound = sfSound_create();
//    sfSound_setBuffer(sound, buffer);

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

//        time_t time_now = time(NULL);
//        if(difftime(time_now, time_last) > 1/60){
//            delay_timer();
//            time_last = time_now;
//        }

//        sfSound_play(sound);

//        if(cpu->sound_timer != 0)



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

        case 0x2000:
            CALL_2nnn(opcode & 0x0FFF);
            break;

        case 0x3000:
            SE_3xkk((opcode & 0x0F00) >> 8, (opcode & 0x00FF));
            break;

        case 0x4000:
            SNE_4xkk((opcode & 0x0F00) >> 8, (opcode & 0x00FF));
            break;

        case 0x5000:
            SE_5xy0((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
            break;

        case 0x6000:
            LD_6xkk((opcode & 0x0F00) >> 8, (opcode & 0x00FF));
            break;

        case 0x7000:
            ADD_7xkk((opcode & 0x0F00) >> 8, (opcode & 0x00FF));
            break;

        case 0x8000:
            switch(opcode & 0x000F)
            {
            case 0x0000:
                LD_8xy0((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                break;

            case 0x0001:
                OR_8xy1((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                break;

            case 0x0002:
                AND_8xy2((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                break;

            case 0x0003:
                XOR_8xy3((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                break;

            case 0x0004:
                ADD_8xy4((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                break;

            case 0x0005:
                SUB_8xy5((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                break;

            case 0x0006:
                SHR_8xy6((opcode & 0x0F00) >> 8);
                break;

            case 0x0007:
                SUBN_8xy7((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                break;

            case 0x000E:
                SHL_8xyE((opcode & 0x0F00) >> 8);
                break;

            }
            break;

        case 0x9000:
            SNE_9xy0((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
            break;

        case 0xA000:
            LD_Annn((opcode & 0x0FFF));
            break;

        case 0xD000:
            DRW_Dxyn((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4, (opcode & 0x000F));
            break;

        case 0xE000:
            switch(opcode & 0x00FF)
            {
            case 0x009E:
                SKP_Ex9E((opcode & 0x0F00) >> 8);
                break;

            case 0x00A1:
                SKNP_ExA1((opcode & 0x0F00) >> 8);
                break;
            }
            break;

        case 0xF000:
            switch(opcode & 0x00FF)
            {

            case 0x0007:
                LD_Fx07((opcode & 0x0F00) >> 8);
                break;

            case 0x000A:
                break;

            case 0x0015:
                LD_Fx15((opcode & 0x0F00) >> 8);
                break;

            case 0x0018:
                LD_Fx18((opcode & 0x0F00) >> 8);
                break;

            case 0x001E:
                ADD_Fx1E((opcode & 0x0F00) >> 8);
                break;

            case 0x0029:
                LD_Fx29((opcode & 0x0F00) >> 8);
                break;

            case 0x0033:
                LD_Fx33((opcode & 0x0F00) >> 8);
                break;

            case 0x0055:
                LD_Fx55((opcode & 0x0F00) >> 8);
                break;

            case 0x0065:
                LD_Fx65((opcode & 0x0F00) >> 8);
                break;
            }
        }
//    }
    }

    sfRenderWindow_destroy(window);

    return 0;
}
