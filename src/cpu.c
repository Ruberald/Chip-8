#include "cpu.h"
#include "keyboard.h"

struct central_processing_unit cpu;

uint8_t zero_flag = 0;

struct central_processing_unit * set_memory(struct memory * mp)
{
    cpu.mem = mp;
    return &cpu;
}

uint8_t * get_mem_pointer()
{
//    if (zero_flag)
//        return cpu.mem->zero_page;
    return cpu.mem->data;
}

int return_pixels(int x, int y)
{
    x = x % 64;
    y = y % 32;
    return (4 * (y * 64 + x));
}

void reset()
{
    cpu.pc = START_ADDRESS;
    cpu.sp = 0;
    cpu.delay_timer = 0;
}

void delay_timer()
{
    if(cpu.delay_timer > 0)
        cpu.delay_timer--;
}

void CLS_00E0()
{
    displayClear();
}

void RET_00EE()
{
    cpu.sp--;
    cpu.pc = cpu.stack[cpu.sp];
}

void JP_1nnn(uint16_t addr)
{
    cpu.pc = (addr);
}

void CALL_2nnn(uint16_t addr)
{
    cpu.stack[cpu.sp] = cpu.pc;
    cpu.sp++;
    cpu.pc = (addr);
}

void SE_3xkk(uint8_t x, uint8_t kk)
{
    if(cpu.Vx[x] == kk)
        cpu.pc += 2;
}

void SNE_4xkk(uint8_t x, uint8_t kk)
{
    if(cpu.Vx[x] != kk)
        cpu.pc += 2;
}

void SE_5xy0(uint8_t x, uint8_t y)
{
    if(cpu.Vx[x] == cpu.Vx[y])
        cpu.pc += 2;
}

void LD_6xkk(uint8_t x, uint8_t kk)
{
    cpu.Vx[x] = kk;
}

void ADD_7xkk(uint8_t x, uint8_t kk)
{
    cpu.Vx[x] += kk;
}

void LD_8xy0(uint8_t x, uint8_t y)
{
    cpu.Vx[x] = cpu.Vx[y];
}

void OR_8xy1(uint8_t x, uint8_t y)
{
    cpu.Vx[x] = cpu.Vx[x] | cpu.Vx[y];
}

void AND_8xy2(uint8_t x, uint8_t y)
{
    cpu.Vx[x] = cpu.Vx[x] & cpu.Vx[y];
}

void XOR_8xy3(uint8_t x, uint8_t y)
{
    cpu.Vx[x] = cpu.Vx[x] ^ cpu.Vx[y];
}

void ADD_8xy4(uint8_t x, uint8_t y)
{
    uint16_t sum = cpu.Vx[x] + cpu.Vx[y];
    if(sum > 255){
        cpu.Vx[x] = sum & 0xFF;
        cpu.Vx[0xF] = 1;
    }
    else{
        cpu.Vx[x] = sum & 0xFF;
        cpu.Vx[0xF] = 0;
    }
}

void SUB_8xy5(uint8_t x, uint8_t y)
{
    uint16_t sub = cpu.Vx[x] - cpu.Vx[y];
    if (cpu.Vx[x] > cpu.Vx[y]){
        cpu.Vx[x] = sub & 0xFF;
        cpu.Vx[0xF] = 1;
    }
    else{
        cpu.Vx[x] = sub & 0xFF;
        cpu.Vx[0xF] = 0;
    }
}

void SHR_8xy6(uint8_t x)
{
    uint8_t value = cpu.Vx[x];
    cpu.Vx[x] >>= 1;
    cpu.Vx[0xF] = (value & 0x1);
}

void SUBN_8xy7(uint8_t x, uint8_t y)
{
    uint16_t sub = cpu.Vx[y] - cpu.Vx[x];
    if (cpu.Vx[y] > cpu.Vx[x]){
        cpu.Vx[x] = sub & 0xFF;
        cpu.Vx[0xF] = 1;
    }
    else{
        cpu.Vx[x] = sub & 0xFF;
        cpu.Vx[0xF] = 0;
    }
}

void SHL_8xyE(uint8_t x)
{
    uint8_t value = cpu.Vx[x];
    cpu.Vx[x] <<= 1;
    cpu.Vx[0xF] = (value & 0x80) >> 7;
}

void SNE_9xy0(uint8_t x, uint8_t y)
{
    if(cpu.Vx[x] != cpu.Vx[y])
        cpu.pc += 2;
}

void LD_Annn(uint16_t addr)
{
    cpu.I = (addr);
    zero_flag = 0;
}

void JP_Bnnn(uint16_t addr)
{
    cpu.pc = (addr) + cpu.Vx[0];
}

void RND_Cxkk(uint8_t x, uint8_t kk)
{
    cpu.Vx[x] = (rand() % 255) & kk;
}

void DRW_Dxyn(uint8_t x, uint8_t y, uint8_t n)
{
    cpu.Vx[0xF] = 0;

    for(int index = 0; index < n; index++)
    {
        uint8_t sprite_byte = get_mem_pointer()[cpu.I + index];

        for(int bit = 0; bit < 8; bit++)
        {
            uint8_t spritePixel = sprite_byte & (0x80 >> bit);

//            uint8_t * displayPixel = &display[4 * (cpu.Vx[x] + bit) * (32 + cpu.Vx[y] + index)];
            uint8_t * displayPixel = &display[return_pixels(cpu.Vx[x] + bit, cpu.Vx[y] + index)];

            if(spritePixel)
            {
                if(*displayPixel)
                {
                    cpu.Vx[0xF] = 1;
                }

                *displayPixel ^= 0xFF;
                *(displayPixel+1) ^= 0xFF;
                *(displayPixel+2) ^= 0xFF;
                *(displayPixel+3) ^= 0xFF;
            }
        }
    }
}

void SKP_Ex9E(uint8_t x)
{
    if(keyboard[cpu.Vx[x]] == 1)
        cpu.pc += 2;
}

void SKNP_ExA1(uint8_t x)
{
    if(keyboard[cpu.Vx[x]] == 0)
        cpu.pc += 2;
}

void LD_Fx07(uint8_t x)
{
    cpu.Vx[x] = cpu.delay_timer;
}

void LD_Fx0A(uint8_t x)
{
    for (uint8_t i = 0; i < 16; i++)
    {
        if(keyboard[i])
        {
            cpu.Vx[x] = i;
            return;
        }
    }

    cpu.pc -= 2;
}

void LD_Fx15(uint8_t x)
{
    cpu.delay_timer = cpu.Vx[x];
}

void LD_Fx18(uint8_t x)
{
    cpu.sound_timer = cpu.Vx[x];
}

void ADD_Fx1E(uint8_t x)
{
    cpu.I = cpu.I + cpu.Vx[x];
    zero_flag = 0;
}

void LD_Fx29(uint8_t x)
{
    cpu.I = (0x50 + 5 * cpu.Vx[x]);
    zero_flag = 1;
}

void LD_Fx33(uint8_t x)
{
    uint8_t temp = cpu.Vx[x];
    get_mem_pointer()[cpu.I] = temp / 100;
    temp %= 100;
    get_mem_pointer()[cpu.I + 1] = temp / 10;
    get_mem_pointer()[cpu.I + 2] = temp % 10;
}

void LD_Fx55(uint8_t x)
{
    for (uint8_t index = 0; index <= x; index++)
    {
        get_mem_pointer()[cpu.I + index] = cpu.Vx[index];
    }
}

void LD_Fx65(uint8_t x)
{
    for (uint8_t index = 0; index <= x; index++)
    {
        cpu.Vx[index] = get_mem_pointer()[cpu.I + index];
    }
}
