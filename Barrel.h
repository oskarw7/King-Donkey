#ifndef BARREL_H

#define BARREL_H


#include "Object.h"
#include "Map.h"

#define BARREL_SIZE 24
#define BARREL_SPEED 1.5
#define BARREL_START_X 60
#define BARREL_START_Y 185
#define BARREL_FREQUENCY 3.0
#define BARREL_TIME_MARGIN 0.01

class Barrel : public Object{
public:
	Barrel(int x, int y, SDL_Surface* texture, SDL_Surface* screen) : Object(x, y, BARREL_SIZE, BARREL_SIZE, texture, screen) {
		this->speed = BARREL_SPEED;
		this->change_direction = 0;
		this->vector = 1;
	};

	void move(int mx, int my);
	int on_ground(Map* map);
	void update(Map* map);
	void barrel_gravity(Map* map);
	int isOut();

	int speed;
private:
	int change_direction;
	int vector;
};

#endif