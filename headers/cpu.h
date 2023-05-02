#include <stdint.h>
#ifndef CPU_H

struct central_processing_unit {
    uint8_t sp;
    uint16_t pc;

    uint16_t stack[16];

    uint8_t Vx[16];

    uint16_t I;
};

#define CPU_H

#endif // CPU_H
