#ifndef GAME_H

#define GAME_H

#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "utils.h"
#include "Player.h"
#include "Floor.h"
#include "Ladder.h"

#define TITLE "King Donkey"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 608
#define	GRAVITY 8

class Game {
public:
	Game();

private:
	int t1, t2, quit, frames, rc;
	double delta, worldTime, fpsTimer, fps, distance, etiSpeed;
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* player_tex;
	SDL_Surface* floor_tex;
	SDL_Surface* ladder_tex;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Player* player; 
	Floor* tiles[SCREEN_WIDTH / FLOOR_SIZE];
	Ladder* ladders[3];

	void init_screen();
	void load_graphics();
	void load_error(SDL_Surface* surface, char* path);
	void start();
	void render();
	void update();
	void stop();
	void key_press(SDL_Keycode key);
	void gravity();
};


#endif
