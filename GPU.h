#ifndef CHIP8_GPU_H
#define CHIP8_GPU_H

#include <cstdint>
#include <SDL.h>


struct Bus;

class GPU {
private:
    Bus& bus;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
public:
    GPU(Bus &_bus);
    ~GPU();

    void clearScreen();
    void renderSprite(int x, int y, uint8_t baseAddress, uint16_t length);
    void setPixel(int x, int y, bool state);
    uint8_t getKey();
};


#endif //CHIP8_GPU_H
