#ifndef CHIP8_BUS_H
#define CHIP8_BUS_H

#include "Memory.h"
#include "Chip8.h"
#include "GPU.h"

struct Bus {
    Memory memory = Memory();
    Chip8 cpu = Chip8(*this);
    GPU gpu = GPU(*this);
};

#endif //CHIP8_BUS_H
