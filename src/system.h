#include <stdint.h>

uint8_t memory[4096];
uint8_t registers[16];
uint16_t program_counter, index_register;

void loadFile(char * fileName);
