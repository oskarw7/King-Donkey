#ifndef PLAYER_H

#define PLAYER_H

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "Object.h"
#include "Ladder.h"
#include "Map.h"

#define PLAYER_SIZE 32
#define PLAYER_SPEED 2
#define PLAYER_LIVES 4
#define JUMP_FORCE 17.5

class Player : public Object {
public:
	Player(int x, int y, SDL_Surface* texture, SDL_Surface* screen) : Object(x, y, PLAYER_SIZE, PLAYER_SIZE, texture, screen) {
		this->speed = PLAYER_SPEED;
		this->lives = PLAYER_LIVES;
	}
	int speed;
	int on_ladder(Map* map);
	int on_ground(Map* map);
	int touch_tile(Map* map);
private:
	int lives;
};
#endif
