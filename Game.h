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
#include "Barrel.h"
#include "BarrelList.h"

#define TITLE "King Donkey"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 700
#define TITLE "King Donkey"
#define CHARSET_PATH "./Assets/cs8x8.bmp"
#define PLAYER_PATH "./Assets/player.bmp"
#define FLOOR_PATH "./Assets/floor.bmp"
#define LADDER_PATH	"./Assets/ladder.bmp"
#define BARREL_PATH "./Assets/barrel.bmp"
#define MAP_FILENAME "./Assets/map.txt"

struct PressedKeys {
	int up;
	int down;
	int left;
	int right;
	int space;
};

class Game {
public:
	Game();

private:
	int quit;
	double worldTime;
	int game_started;

	SDL_Event event;

	SDL_Surface* screen;
	SDL_Surface* charset;
	SDL_Surface* player_tex;
	SDL_Surface* floor_tex;
	SDL_Surface* ladder_tex;
	SDL_Surface* barrel_tex;

	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Player* player; 
	Map* map;
	BarrelList barrels;

	struct PressedKeys pk = {0, 0, 0, 0, 0};

	void init_screen();
	void load_graphics();
	void load_error(SDL_Surface* surface, char* path);
	void start();
	void render();
	void update();
	void stop();
	void players_gravity();
	void draw_map();
	void manage_time(double* delta, double* t1, double* t2, double* worldTime, double* fpsTimer, double* fps, int* frames);
	void hit_barrel();
};


#endif
