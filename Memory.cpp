#include <cstdio>
#include <cstring>
#include <iostream>
#include "Memory.h"

uint8_t Memory::read(uint16_t pos) {
    if (pos >= 0 && pos < 4096)
        return memory[pos];
}

void Memory::write(uint16_t pos, uint8_t data) {
    if (pos >= 0 && pos < 4096)
        memory[pos] = data;
}

void Memory::readFile(char *name) {
    FILE *fp = fopen(name, "r");
    if (fp == NULL) {
        std::cout << "The file couldn't be found!" << std::endl;
        return;
    }

    uint16_t size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    auto *buffer = new uint8_t[size];
    fread(buffer, 1, size, fp);
    fclose(fp);

    std::memcpy(&memory[512], buffer, size);
}
