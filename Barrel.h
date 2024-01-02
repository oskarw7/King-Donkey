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

#define JUMP_HITBOX_OFFSET 30

class Barrel : public Object{
public:
	Barrel(int x, int y, SDL_Surface* texture, SDL_Surface* screen) : Object(x, y, BARREL_SIZE, BARREL_SIZE, texture, screen) {
		this->speed = BARREL_SPEED;
		this->change_direction = 0;
		this->vector = 1;
		jump_hitbox = new Object(x, y - JUMP_HITBOX_OFFSET, BARREL_SIZE, BARREL_SIZE + JUMP_HITBOX_OFFSET, NULL, NULL);
		this->player_hit = 0;
	};

	int on_ground(Map* map);
	void update(Map* map);
	void barrel_gravity(Map* map);
	int isOut();

	int speed;
	Object* jump_hitbox;
	int player_hit;
private:
	int change_direction;
	int vector;
};

#endif