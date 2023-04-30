#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "system.h"

void readFile(char * fileName)
{
	FILE * file;
	char ch;
	int index = 0;
	
	if((file = fopen(fileName, "rb")) == NULL){
		printf("Error reading file\n");
		exit(EXIT_FAILURE);
	}

	while((ch = getc(file)) != EOF){
		printf("%x", ch);
		memory[index] = ch;
	}

	printf("%s\n%s\n", memory[1], memory[4]);

	fclose(file);
}

int main(void)
{
	readFile("src\\IBM Logo.ch8");

	return 0;
}
