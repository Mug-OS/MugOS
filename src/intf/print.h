#pragma once

#include <stdint.h>
#include <stddef.h>

struct color {
	unsigned char R;
    unsigned char G;
    unsigned char B;
}

void printClear();
void printChar(char character);
void printStr(char* string);
void printSetColor(uint8_t foreground, uint8_t background);