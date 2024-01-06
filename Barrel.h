#ifndef BARREL_H

#define BARREL_H


#include "Object.h"
#include "Map.h"
#include "Animation.h"

#define BARREL_WIDTH 22
#define BARREL_HEIGHT 18
#define BARREL_SPEED 1.5
#define BARREL_START_X 83
#define BARREL_START_Y 185
#define BARREL_FREQUENCY 3.0
#define BARREL_TIME_MARGIN 0.01
#define JUMP_HITBOX_OFFSET 30

class Barrel : public Object {
public:
	Barrel(int x, int y, SDL_Surface* texture, int frame_width, SDL_Surface* screen) : Object(x, y, BARREL_WIDTH, BARREL_HEIGHT, screen) {
		this->speed = BARREL_SPEED;
		this->change_direction = 0;
		this->vector = 1;
		jump_hitbox = new Object(x, y - JUMP_HITBOX_OFFSET, BARREL_WIDTH, BARREL_HEIGHT + JUMP_HITBOX_OFFSET, NULL);
		this->texture = texture;
		this->player_hit = 0;
		animation = new Animation(texture, BARREL_WIDTH, 0.25);
	};

	void draw(double time);
	int on_ground(Map* map);
	void update(Map* map, double delta);
	void barrel_gravity(Map* map, double delta);
	int isOut();

	int speed;
	Object* jump_hitbox;
	SDL_Surface* texture;
	int player_hit;
private:
	int change_direction;
	int vector;
	Animation* animation;
};

#endif