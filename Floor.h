#ifndef FLOOR_H

#define FLOOR_H

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "Object.h"
#define FLOOR_SIZE 32

class Floor : public Object {
public:
	Floor(int x, int y, SDL_Surface* texture, SDL_Surface* screen) : Object(x, y, FLOOR_SIZE, FLOOR_SIZE, texture, texture->w, screen) {};
};

#endif