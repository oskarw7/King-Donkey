#ifndef FLOOR_H

#define FLOOR_H

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "StaticObject.h"

#define FLOOR_SIZE 32

class Floor : public StaticObject {
public:
	Floor(int x, int y, SDL_Surface* texture, SDL_Surface* screen) : StaticObject(x, y, FLOOR_SIZE, FLOOR_SIZE, texture, screen) {
		this->texture = texture;
	};
private:
	SDL_Surface* texture;
};

#endif