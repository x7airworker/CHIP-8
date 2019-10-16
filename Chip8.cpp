#include <iostream>
#include "Chip8.h"
#include "Bus.h"

Chip8::Chip8(Bus &_bus) : bus(_bus) {}

void Chip8::launch() {
    while(true) {
        bool result = cycle();
        if (!result) {
            std::cout << "Error processing instruction!" << std::endl;
            break;
        }
        pointer += 2;
    }
}

bool Chip8::cycle() {
    uint8_t firstByte = bus.memory.read(pointer);
    uint8_t secondByte = bus.memory.read(pointer + 1);
    uint16_t instruction = firstByte << 8 | secondByte;
    std::cout << "Instruction:" << std::hex << instruction << std::endl;

    uint16_t opcode = firstByte >> 4;
    std::cout << "Opcode:" << std::hex << opcode << std::endl;

    if (opcode == 0x6) {
        uint16_t register_id = (((instruction >> 8) << 4) & 0xff) >> 4;
        regV[register_id] = secondByte;
        return true;
    } else if (opcode == 0x0) {
        if (secondByte == 0xe0) {
            bus.gpu.clearScreen();
            return true;
        } else if (secondByte == 0xEE) {
            pointer = subroutineLoc + 2;
            return true;
        }
    } else if (opcode == 0xC) {
        uint16_t register_id = (((instruction >> 8) << 4) & 0xff) >> 4;
        std::uniform_int_distribution<int> dist(0, secondByte);
        int random = dist(rd);
        regV[register_id] = random;
        return true;
    } else if (opcode == 0xA) {
        uint16_t address = (instruction << 4);
        I = address >> 4;
        return true;
    } else if (opcode == 0xF) {
        uint16_t register_id = (((instruction >> 8) << 4) & 0xff) >> 4;
        uint8_t vx = regV[register_id];
        if (secondByte == 0x33) {
            bus.memory.write(I + 2, vx % 10);
            bus.memory.write(I + 1, (vx / 10) % 10);
            bus.memory.write(I, (vx / 100)  % 10);
            return true;
        } else if (secondByte == 0x65) {
            for (int i = 0; i <= register_id; i++) {
                regV[i] = bus.memory.read(I + i);
            }
            I += register_id + 1;
            return true;
        } else if (secondByte == 0x29) {
            I = vx * 5;
            return true;
        } else if (secondByte == 0x0A) {
            regV[register_id] = bus.gpu.getKey();
            return true;
        } else if (secondByte == 0x55) {
            for (int i = 0; i <= register_id; i++) {
                bus.memory.write(I + i, regV[i]);
            }
            I += register_id + 1;
            return true;
        } else if(secondByte == 0x1E) {
            I += vx;
            return true;
        }
    } else if (opcode == 0xD) {
        uint16_t x = regV[(((instruction >> 8) << 4) & 0xff) >> 4];
        uint16_t y = regV[(instruction << 8) >> 12];
        uint16_t length = (instruction << 12);
        length >>= 12;
        bus.gpu.renderSprite(x, y, I, length);
        return true;
    } else if (opcode == 0x7) {
        regV[(((instruction >> 8) << 4) & 0xff) >> 4] += secondByte;
        return true;
    } else if (opcode == 0x1) {
        uint16_t address = (instruction << 4);
        address >>= 4;
        pointer = address - 2; //because the cpu adds 2
        return true;
    } else if (opcode == 0x8) {
        uint16_t type = (instruction << 12);
        if (type == 0x0) {
            regV[(((instruction >> 8) << 4) & 0xff) >> 4] = regV[(instruction << 8) >> 12];
            return true;
        }
    } else if (opcode == 0x3) {
        uint16_t x = regV[(((instruction >> 8) << 4) & 0xff) >> 4];
        if (x == secondByte) {
            pointer += 2;
        }
        return true;
    } else if (opcode == 0x4) {
        uint16_t x = regV[(((instruction >> 8) << 4) & 0xff) >> 4];
        if (x != secondByte) {
            pointer += 2;
        }
        return true;
    }else if (opcode == 0x2) {
        uint16_t address = (instruction << 4);
        address >>= 4;
        subroutineLoc = pointer;
        pointer = address - 2; //because the cpu adds 2
        return true;
    }

    return false;
}