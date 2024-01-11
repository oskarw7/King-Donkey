#ifndef BARREL_H

#define BARREL_H

#include "Object.h"
#include "Map.h"
#include "Animation.h"

#define BARREL_WIDTH 22 //pixele
#define BARREL_HEIGHT 18 //pixele
#define HORIZONTAL_BARREL 27 //pixele
#define BARREL_VELOCITY_X 150.0 //pixele/s
#define BARREL_VELOCITY_Y 250.0 //pixele/s
#define BARREL_START_X 83 //pixele
#define BARREL_START_Y 189 //pixele
#define BARREL_FREQUENCY 3.0 //s
#define BARREL_TIME_MARGIN 0.01 //s
#define JUMP_HITBOX_OFFSET 40 //pixele
#define ROLLING_PATH "./Assets/barrel_sheet.bmp"
#define FALLING_PATH "./Assets/spinning_barrels.bmp"

struct BarrelAnimations {
	Animation* rolling; //ruch poziomy
	Animation* falling; //ruch pionowy
};

class Barrel : public Object {
public:
	Barrel(double x, double y, double frame_width, SDL_Surface* screen) : Object(x, y, BARREL_WIDTH, BARREL_HEIGHT, screen) {
		this->velocity_x = BARREL_VELOCITY_X;
		this->velocity_y = BARREL_VELOCITY_Y;
		this->change_direction = 0;
		this->vector = 1;
		this->jump_hitbox1 = new Object(x, y - JUMP_HITBOX_OFFSET, BARREL_WIDTH, BARREL_HEIGHT + JUMP_HITBOX_OFFSET/2, NULL);
		this->jump_hitbox2 = new Object(x - 10 * JUMP_HITBOX_OFFSET, y, 10 * JUMP_HITBOX_OFFSET, BARREL_HEIGHT, NULL);
		this->jump_hitbox3 = new Object(x + BARREL_WIDTH, y, 10 * JUMP_HITBOX_OFFSET, BARREL_HEIGHT, NULL);
		this->checkpoint1 = 0;
		this->checkpoint2 = 0;
		this->checkpoint3 = 0;
		this->texture = texture;
		this->player_hit = 0;
		this->player_jump = 0;
		load_barrel_graphics();
		current_animation = animations.rolling;
	};

	void draw(double time, Map* map);
	int on_ground(Map* map);
	void update(Map* map, double delta);
	void barrel_gravity(Map* map, double delta);
	int isOut();
	void reset();

	double velocity_x;
	double velocity_y;

	Object* jump_hitbox1;
	Object* jump_hitbox2;
	Object* jump_hitbox3;

	SDL_Surface* texture;
	SDL_Surface* rolling_tex;
	SDL_Surface* falling_tex;

	struct BarrelAnimations animations;
	Animation* current_animation;

	int checkpoint1;
	int checkpoint2;
	int checkpoint3;
	int player_hit;
	int player_jump;

	~Barrel();
private:
	int change_direction;
	int vector;

	void load_barrel_graphics();
};

#endif