#include <iostream>
#include "GPU.h"
#include "Bus.h"

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

GPU::GPU(Bus &_bus) : bus(_bus) {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        if (SDL_CreateWindowAndRenderer(640, 320, 0, &window, &renderer) == 0) {
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }
}

void GPU::clearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void GPU::renderSprite(int x, int y, uint8_t baseAddress, uint16_t length) {
    for (int currY = 0; currY < length; currY++) {
        uint16_t currByte = bus.memory.read(baseAddress);
        for (int currX = 0; currX < 8; currX++) {
            uint16_t curr = currByte << (currX + 8);
            curr >>= 15;
            setPixel(x + currX, y + currY, curr);
        }
        baseAddress++;
    }
}

uint8_t GPU::getKey() {
    static SDL_Event event;
    while (true) {
        while ( SDL_PollEvent( &event ) ) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    return reinterpret_cast<long>(&event.key.keysym.scancode);
            }
        }

#ifdef LINUX
        usleep(10);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef WINDOWS
        Sleep(10);
#endif
    }
}

GPU::~GPU() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void GPU::setPixel(int x, int y, bool state) {
    if (!state)
        return;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect = {
            .x =  x * 10,
            .y = y * 10,
            .w = 10,
            .h = 10
    };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

