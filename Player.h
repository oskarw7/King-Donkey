#ifndef PLAYER_H

#define PLAYER_H

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}


#include "Object.h"
#include "Map.h"
#include "Animation.h"

#define RUN_LEFT_PATH "./Assets/run_left.bmp"
#define RUN_RIGHT_PATH "./Assets/run_right.bmp"
#define CLIMB_PATH "./Assets/climb.bmp"
#define STEADY_CLIMB_PATH "./Assets/steady_climb.bmp"
#define BACK_PATH "./Assets/turn_back.bmp"
#define STAND_LEFT_PATH "./Assets/stand_left.bmp"
#define STAND_RIGHT_PATH "./Assets/stand_right.bmp"
#define	JUMP_LEFT_PATH "./Assets/jump_left.bmp"
#define	JUMP_RIGHT_PATH "./Assets/jump_right.bmp"

#define PLAYER_WIDTH 28
#define PLAYER_HEIGHT 30
#define PLAYER_VELOCITY_X 200.0
#define CLIMB_VELOCITY 200.0
#define PLAYER_LIVES 4
#define JUMP_VELOCITY 225.0
#define SPEED_X_COOLDOWN 125.0

struct PlayerAnimations {
	Animation* run_left;
	Animation* run_right;
	Animation* climb;
	Animation* steady_climb;
	Animation* back;
	Animation* stand_left;
	Animation* stand_right;
	Animation* jump_left;
	Animation* jump_right;
};

class Player : public Object {
public:
	Player(int x, int y, SDL_Surface* screen) : Object(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, screen) {
		this->velocity_x = PLAYER_VELOCITY_X;
		this->velocity_y = 0;
		this->climb_velocity = CLIMB_VELOCITY;
		this->isJumping = 0;
		this->lives = PLAYER_LIVES;
		this->score = 0;
		load_player_graphics();
		current_animation = animations.stand_left;
	}
	int score;
	int isJumping;
	double velocity_x;
	double velocity_y;
	double climb_velocity;
	int lives;

	struct PlayerAnimations animations;
	Animation* current_animation;

	void player_move(int mx, int my);
	void draw(double time, Map* map);
	int on_ladder(Map* map);
	int on_ground(Map* map);
	int touch_tile(Map* map);
	int above_ladder(Map* map);
	int on_upper_ladder(Map* map);

	~Player();
private:
	SDL_Surface* run_left_tex;
	SDL_Surface* run_right_tex;
	SDL_Surface* climb_tex;
	SDL_Surface* steady_climb_tex;
	SDL_Surface* back_tex;
	SDL_Surface* stand_left_tex;
	SDL_Surface* stand_right_tex;
	SDL_Surface* jump_left_tex;
	SDL_Surface* jump_right_tex;

	void load_player_graphics();
};
#endif
