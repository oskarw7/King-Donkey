#ifndef PLAYER_H

#define PLAYER_H

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "Object.h"
#include "Ladder.h"
#include "Map.h"
#include "Floor.h"

#define PLAYER_SIZE 30
#define PLAYER_SPEED 3
#define PLAYER_LIVES 4
#define JUMP_FORCE 20

class Player : public Object {
public:
	Player(int x, int y, SDL_Surface* texture, int frame_width, SDL_Surface* screen) : Object(x, y, PLAYER_SIZE, PLAYER_SIZE, texture, frame_width, screen) {
		this->speed = PLAYER_SPEED;
		this->lives = PLAYER_LIVES;
		this->score = 0;
	}
	int score;
	int speed;
	int lives;

	void player_move(int mx, int my);
	int on_ladder(Map* map);
	int on_ground(Map* map);
	int touch_tile(Map* map);
	int above_ladder(Map* map);
	int on_upper_ladder(Map* map);
private:
	
};
#endif
