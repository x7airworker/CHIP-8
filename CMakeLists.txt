cmake_minimum_required(VERSION 3.15)
project(chip8)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
set(SDL2_INCLUDE_DIR=/usr/include/SDL2)
set(SDL2_LIBRARY /usr/lib/libSDL2.so)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(chip8)
link_directories(chip8)

set(CMAKE_CXX_STANDARD 17)
SET( PROJ_LIBRARIES ${SDL_LIBRARY} )
add_executable(chip8 main.cpp Memory.cpp Memory.h Bus.h Chip8.cpp Chip8.h GPU.cpp GPU.h)
target_link_libraries(chip8 ${SDL2_LIBRARY})