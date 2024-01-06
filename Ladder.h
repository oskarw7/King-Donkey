#ifndef LADDER_H

#define LADDER_H

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "StaticObject.h"

#define LADDER_SIZE 32

class Ladder : public StaticObject {
public:
	Ladder(int x, int y, SDL_Surface* texture, SDL_Surface* screen) : StaticObject(x, y, LADDER_SIZE, LADDER_SIZE, texture, screen) {
		this->texture = texture;
	};
private:
	SDL_Surface* texture;
};

#endif