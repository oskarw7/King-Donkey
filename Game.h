#ifndef GAME_H

#define GAME_H

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "utils.h"
#include "Player.h"
#include "Barrel.h"
#include "BarrelList.h"
#include "DonkeyKong.h"
#include "ScorePlate.h"

#define TITLE "King Donkey"
#define SCREEN_WIDTH 800		//pixele
#define SCREEN_HEIGHT 750		//pixele
#define MAP_COUNT 3

#define MENU_BOX_WIDTH 300		//pixele
#define MENU_BOX_HEIGHT 50		//pixele
#define MENU_BOX_START_Y 300	//pixele
#define MENU_BOX_OFFSET 70		//pixele

#define HEART_WIDTH 25			//pixele
#define HEART_START_X 20		//pixele
#define HEART_START_Y 70		//pixele

//sciezki do bitmap i map
#define CHARSET_PATH "./Assets/cs8x8.bmp"
#define LOGO_PATH "./Assets/logo.bmp"
#define FLOOR_PATH "./Assets/floor.bmp"
#define FLOOR2_PATH "./Assets/floor2.bmp"
#define FLOOR3_PATH "./Assets/floor3.bmp"
#define LADDER_PATH	"./Assets/ladder.bmp"
#define BARREL_PATH "./Assets/barrel_sheet.bmp"
#define STANDING_BARREL_PATH "./Assets/standing_barrel.bmp"
#define PRINCESS_PATH	"./Assets/princess.bmp"
#define TROPHY_PATH "./Assets/trophy.bmp"
#define HEART_PATH "./Assets/heart.bmp"
#define DONKEY_KONG_PATH "./Assets/donkey_kong_sheet.bmp"
#define MAP1_FILENAME "./Assets/map1.txt"
#define MAP2_FILENAME "./Assets/map2.txt"
#define MAP3_FILENAME "./Assets/map3.txt"

//przechowuje informacje o wcisnietych klawiszach
struct PressedKeys { 
	int up;
	int down;
	int left;
	int right;
	int space;
};

struct MenuKeys {
	int scroll_up;
	int scroll_down;
	int enter;
	int exit;
	int index;
};

struct Colors {
	int black;
	int green;
	int red;
	int blue;
};

class Game {
public:
	Game();

private:
	//flagi
	int game_started, game_paused, menu, map_mode, scoreboard_mode;
	int maps_completed[MAP_COUNT];
	//czas gry od utworzenia nowej gry
	double worldTime;

	SDL_Event event;

	SDL_Surface* screen;
	SDL_Surface* charset;
	SDL_Surface* logo_tex;
	SDL_Surface* floor_tex;
	SDL_Surface* floor2_tex;
	SDL_Surface* floor3_tex;
	SDL_Surface* ladder_tex;
	SDL_Surface* barrel_tex;
	SDL_Surface* standing_barrel_tex;
	SDL_Surface* princess_tex;
	SDL_Surface* trophy_tex;
	SDL_Surface* heart_tex;
	SDL_Surface* donkey_kong_tex;
	SDL_Surface* plus100_tex;
	SDL_Surface* plus300_tex;

	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Player* player; 
	Map* map;
	Map* map1;
	Map* map2;
	Map* map3;
	BarrelList barrels;
	DonkeyKong* donkey_kong;
	ScorePlate* score_plate;

	struct PressedKeys pk;
	struct MenuKeys mk;

	void init_screen();
	void init_keys();
	void load_graphics();
	void load_error(SDL_Surface* surface, char* path);
	void start();
	void render();
	void render_menu(Colors colors);
	void update(double delta);
	void handle_menu();
	void check_static_animations();
	void draw_lives();
	void manage_time(double* delta, double* t1, double* t2, double* worldTime, double* fpsTimer, double* fps, int* frames);
	void hit_barrel();
	void change_map(int map_number);
	void check_ending();
	void check_trophy();
	void reset_game_state();
	void stop();
};


#endif
