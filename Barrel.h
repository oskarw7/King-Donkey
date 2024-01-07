#ifndef BARREL_H

#define BARREL_H

#include "Object.h"
#include "Map.h"
#include "Animation.h"

#define BARREL_WIDTH 22
#define BARREL_HEIGHT 18
#define HORIZONTAL_BARREL 27
#define BARREL_VELOCITY_X 150.0
#define BARREL_VELOCITY_Y 250.0
#define BARREL_START_X 83
#define BARREL_START_Y 189
#define BARREL_FREQUENCY 3.0
#define BARREL_TIME_MARGIN 0.01
#define JUMP_HITBOX_OFFSET 60
#define ROLLING_PATH "./Assets/barrel_sheet.bmp"
#define FALLING_PATH "./Assets/spinning_barrels.bmp"

struct BarrelAnimations {
	Animation* rolling;
	Animation* falling;
};

class Barrel : public Object {
public:
	Barrel(int x, int y, int frame_width, SDL_Surface* screen) : Object(x, y, BARREL_WIDTH, BARREL_HEIGHT, screen) {
		this->velocity_x = BARREL_VELOCITY_X;
		this->velocity_y = 0;
		this->change_direction = 0;
		this->vector = 1;
		jump_hitbox = new Object(x, y - JUMP_HITBOX_OFFSET, BARREL_WIDTH, BARREL_HEIGHT + JUMP_HITBOX_OFFSET, NULL);
		this->texture = texture;
		this->player_hit = 0;
		load_barrel_graphics();
		current_animation = animations.rolling;
	};

	void draw(double time);
	int on_ground(Map* map);
	void update(Map* map, double delta);
	void barrel_gravity(Map* map, double delta);
	int isOut();

	double velocity_x;
	double velocity_y;
	Object* jump_hitbox;
	SDL_Surface* texture;
	SDL_Surface* rolling_tex;
	SDL_Surface* falling_tex;
	int player_hit;
	struct BarrelAnimations animations;
	Animation* current_animation;

	~Barrel();
private:
	int change_direction;
	int vector;
	void load_barrel_graphics();
};

#endif