#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "memory.h"

struct memory mem;

void readFile(char * fileName)
{
	FILE * file;
	char ch;
	int index = 0;
	
    file = fopen(fileName, "rb");

    if((file) == NULL){
        fprintf(stderr, "[FAILED] Error reading file\n");
		exit(EXIT_FAILURE);
    }

    fread(mem.data, 1, sizeof(mem.data), file);

	fclose(file);
}

struct memory * init_mem(char * fileName)
{
    memset(mem.zero_page, 0, sizeof(mem.zero_page));

    readFile(fileName);

    return &mem;
}
