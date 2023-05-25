#include <stdint.h>
#include <stdlib.h>
#include "memory.h"
#include "display.h"

#define START_ADDRESS 0x0000

#ifndef CPU_H

#define CPU_H

struct central_processing_unit {

    struct memory * mem;

    uint8_t sp;
    uint16_t pc;

    uint16_t stack[16];

    uint8_t Vx[16];

    uint16_t I;

    uint8_t delay_timer;
    uint8_t sound_timer;

    uint16_t keypad[16];
};

struct central_processing_unit * set_memory(struct memory * mp);

void reset();

void CLS_00E0();

void RET_00EE();

void JP_1nnn(uint16_t addr);

void CALL_2nnn(uint16_t addr);

void SE_3xkk(int x, uint8_t kk);

void SNE_4xkk(int x, uint8_t kk);

void SE_5xy0(int x, int y);

void LD_6xkk(uint8_t x, uint8_t kk);

void ADD_7xkk(uint8_t x, uint8_t kk);

void SUB_8xy5(int x, int y);

void LD_8xy0(int x, int y);

void OR_8xy1(int x, int y);

void AND_8xy2(int x, int y);

void XOR_8xy3(int x, int y);

void ADD_8xy4(int x, int y);

void SUB_8xy5(int x, int y);

void SHR_8xy6(int x);

void SUBN_8xy7(int x, int y);

void SHL_8xyE(int x);

void SNE_9xy0(int x, int y);

void LD_Annn(uint16_t addr);

void JP_Bnnn(uint16_t addr);

void RND_Cxkk(int x, uint8_t kk);

void DRW_Dxyn(uint8_t x, uint8_t y, uint8_t n);

#endif // CPU_H
