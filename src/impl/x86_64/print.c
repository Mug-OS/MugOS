#include "print.h"

const static size_t numCols = 80;
const static size_t numRows = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

char stringReachEnd = 0; // 0 = false, 1 = true

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = printColorWhite | printColorBlack << 4;

void clearRow(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < numCols; col++) {
        buffer[col + numCols * row] = empty;
    }
}

void printClear() {
    for (size_t i = 0; i < numRows; i++) {
        clearRow(i);
    }
}

void printNewline() {
    col = 0;

    if (row < numRows - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < numRows; row++) {
        for (size_t col = 1; col < numCols; col++) {
            struct Char character = buffer[col + numCols * row];
            buffer[col + numCols * (row - 1)] = character;
        }    
    }

    clearRow(numCols - 1);
}

void printChar(char character) {
    if (character == '\n') {
        printNewline();
        return;
    }

    if (col > (numCols) - 1) {
        printNewline();
    }

    buffer[col + numCols * row] = (struct Char) {
        character: (uint8_t) character,
        color: color,
    };

    col++;
}

void printStr(char* text) {
    for (size_t i = 0; (stringReachEnd == 0); i++) {
        char character = (uint8_t) text[i];

        if (character == '\0') {
            stringReachEnd = 1;
            return;
        }

        printChar(character);
    }
}

void printSetColor(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}