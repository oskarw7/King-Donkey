#ifndef BARREL_H

#define BARREL_H


#include "Object.h"
#include "Map.h"

#define BARREL_SIZE 20
#define BARREL_SPEED 4

class Barrel : public Object{
public:
	Barrel(int x, int y, int width, int height, SDL_Surface* texture, SDL_Surface* screen) : Object(x, y, BARREL_SIZE, BARREL_SIZE, texture, screen) {};
	int on_ground(Map* map);
	void update();

	int speed;
private:
};

#endif