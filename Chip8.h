#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include <cstdint>
#include <random>

struct Bus;

class Chip8 {
public:
    explicit Chip8(Bus& _bus);
    void launch();
private:
    Bus& bus;
    uint16_t pointer = 0x200;
    uint8_t regV[15] = {};
    uint16_t I; //pointer to address
    uint16_t subroutineLoc;
    std::random_device rd;
    bool cycle();
};


#endif //CHIP8_CHIP8_H
