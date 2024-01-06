#ifndef PLAYER_H

#define PLAYER_H

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include <iostream>
#include "Object.h"
#include "Ladder.h"
#include "Map.h"
#include "Floor.h"
#include "Animation.h"

#define WALKING_LEFT_PATH "./Assets/run_left.bmp"
#define WALKING_RIGHT_PATH "./Assets/run_right.bmp"
#define CLIMB_PATH "./Assets/climb.bmp"
#define STEADY_CLIMB_PATH "./Assets/steady_climb.bmp"
#define BACK_PATH "./Assets/turn_back.bmp"
#define STANDING_LEFT_PATH "./Assets/stand_left.bmp"
#define STANDING_RIGHT_PATH "./Assets/stand_right.bmp"
#define	JUMPING_LEFT_PATH "./Assets/jump_left.bmp"
#define	JUMPING_RIGHT_PATH "./Assets/jump_right.bmp"


#define PLAYER_WIDTH 28
#define PLAYER_HEIGHT 30
#define PLAYER_SPEED 3
#define PLAYER_LIVES 4
#define JUMP_FORCE 20

struct PlayerAnimations {
	Animation* walking_left;
	Animation* walking_right;
	Animation* climb;
	Animation* steady_climb;
	Animation* back;
	Animation* standing_left;
	Animation* standing_right;
	Animation* jump_left;
	Animation* jump_right;
};

class Player : public Object {
public:
	Player(int x, int y, SDL_Surface* screen) : Object(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, screen) {
		this->speed = PLAYER_SPEED;
		this->lives = PLAYER_LIVES;
		this->score = 0;
		load_player_graphics();
		current_animation = animations.standing_left;
	}
	int score;
	int speed;
	int lives;

	struct PlayerAnimations animations;
	Animation* current_animation;

	void player_move(int mx, int my);
	void draw(double time);
	int on_ladder(Map* map);
	int on_ground(Map* map);
	int touch_tile(Map* map);
	int above_ladder(Map* map);
	int on_upper_ladder(Map* map);
	SDL_Surface* walking_left_tex;
	SDL_Surface* walking_right_tex;
	SDL_Surface* climb_tex;
	SDL_Surface* steady_climb_tex;
	SDL_Surface* back_tex;
	SDL_Surface* standing_left_tex;
	SDL_Surface* standing_right_tex;
	SDL_Surface* jumping_left_tex;
	SDL_Surface* jumping_right_tex;
private:
	void load_player_graphics();
};
#endif
