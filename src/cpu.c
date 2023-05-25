#include "cpu.h"

struct central_processing_unit cpu;

struct central_processing_unit * set_memory(struct memory * mp)
{
    cpu.mem = mp;
    return &cpu;
}

void reset()
{
    cpu.pc = START_ADDRESS;
}

void CLS_00E0()
{
    displayClear();
}

void RET_00EE()
{
    cpu.pc = cpu.stack[cpu.sp];
    cpu.sp--;
}

void JP_1nnn(uint16_t addr)
{
    cpu.pc = addr;
}

void CALL_2nnn(uint16_t addr)
{
    cpu.stack[cpu.sp] = cpu.pc;
    cpu.sp++;
    cpu.pc = addr;
}

void SE_3xkk(int x, uint8_t kk)
{
    if(cpu.Vx[x] == kk)
        cpu.pc += 2;
}

void SNE_4xkk(int x, uint8_t kk)
{
    if(cpu.Vx[x] != kk)
        cpu.pc += 2;
}

void SE_5xy0(int x, int y)
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

void LD_8xy0(int x, int y)
{
    cpu.Vx[x] = cpu.Vx[y];
}

void OR_8xy1(int x, int y)
{
    cpu.Vx[x] = cpu.Vx[x] | cpu.Vx[y];
}

void AND_8xy2(int x, int y)
{
    cpu.Vx[x] = cpu.Vx[x] & cpu.Vx[y];
}

void XOR_8xy3(int x, int y)
{
    cpu.Vx[x] = cpu.Vx[x] ^ cpu.Vx[y];
}

void ADD_8xy4(int x, int y)
{
    if((cpu.Vx[x] + cpu.Vx[y]) > 255){
        cpu.Vx[0xF] = 1;
        cpu.Vx[x] = (cpu.Vx[x] + cpu.Vx[y]) & 0xFF;
    }
    else
        cpu.Vx[x] = cpu.Vx[x] + cpu.Vx[y];

}

void SUB_8xy5(int x, int y)
{
    if (cpu.Vx[x] > cpu.Vx[y])
        cpu.Vx[0xF] = 1;
    cpu.Vx[x] = cpu.Vx[x] - cpu.Vx[y];
}

void SHR_8xy6(int x)
{
    cpu.Vx[0xF] = (cpu.Vx[x] & 0x1);
    cpu.Vx[x] >>= 1;
}

void SUBN_8xy7(int x, int y)
{
    if (cpu.Vx[y] > cpu.Vx[x])
        cpu.Vx[0xF] = 1;
    cpu.Vx[x] = cpu.Vx[y] - cpu.Vx[x];
}

void SHL_8xyE(int x)
{
    cpu.Vx[0xF] = (cpu.Vx[x] & 0x1);
    cpu.Vx[x] >>= 1;
}

void SNE_9xy0(int x, int y)
{
    if(cpu.Vx[x] != cpu.Vx[y])
        cpu.pc += 2;
}

void LD_Annn(uint16_t addr)
{
    cpu.I = (addr - 0x200);
}

void JP_Bnnn(uint16_t addr)
{
    cpu.pc = addr + cpu.Vx[0];
}

void RND_Cxkk(int x, uint8_t kk)
{
    cpu.Vx[x] = (rand() % 255) & kk;
}

void DRW_Dxyn(uint8_t x, uint8_t y, uint8_t n)
{
    cpu.Vx[0xF] = 0;

    for(int index = 0; index < n; index++)
    {
        uint8_t sprite_byte = cpu.mem->data[cpu.I + index];

        for(int bit = 0; bit < 8; bit++)
        {
            uint8_t spritePixel = sprite_byte & (0x80 >> bit);

            uint8_t * displayPixel = &display[cpu.Vx[x] + bit][cpu.Vx[y] + index];

            if(spritePixel)
            {
                if(*displayPixel)
                {
                    cpu.Vx[0xF] = 1;
                }

                *displayPixel ^= 0xFF;
            }
        }
    }
}
