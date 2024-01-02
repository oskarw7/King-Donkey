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
#include "Princess.h"

#define TITLE "King Donkey"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 750
#define CHARSET_PATH "./Assets/cs8x8.bmp"
#define PLAYER_PATH "./Assets/player.bmp"
#define FLOOR_PATH "./Assets/floor.bmp"
#define LADDER_PATH	"./Assets/ladder.bmp"
#define BARREL_PATH "./Assets/barrel.bmp"
#define PRINCESS_PATH	"./Assets/princess.bmp"
#define TROPHY_PATH "./Assets/trophy.bmp"
#define MAP1_FILENAME "./Assets/map1.txt"
#define MAP2_FILENAME "./Assets/map2.txt"
#define MAP3_FILENAME "./Assets/map3.txt"

#define TPS 60

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
	int first_completed, second_completed, third_completed;

	SDL_Event event;

	SDL_Surface* screen;
	SDL_Surface* charset;
	SDL_Surface* player_tex;
	SDL_Surface* floor_tex;
	SDL_Surface* ladder_tex;
	SDL_Surface* barrel_tex;
	SDL_Surface* princess_tex;
	SDL_Surface* trophy_tex;

	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Player* player; 
	Map* map;
	BarrelList barrels;
	Princess* princess;

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
	void change_map();
	void check_princess();
	void check_trophy();
};


#endif
