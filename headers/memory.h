#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#define MEM_SIZE 1024 * 4

struct memory {
  uint8_t zero_page[0x200];
  uint8_t data[MEM_SIZE - 0x200];
};

void readFile(char * fileName);

struct memory * init_mem(char * fileName);

#endif // MEMORY_H
