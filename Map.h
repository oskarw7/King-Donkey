#ifndef MAP_H
#define MAP_H

#include "Object.h"
#include "StaticObject.h"
#include "ObjectList.h"
#include "utils.h"

#include <string.h>
#include <stdio.h>

#define MAP_HEIGHT 21
#define MAP_WIDTH 25
#define MAP_PATH_LENGTH 17
#define FLOOR_SIZE 32
#define LADDER_SIZE 32
#define PRINCESS_WIDTH 23
#define PRINCESS_HEIGHT 32
#define ENDING_AREA_WIDTH 32*3
#define ENDING_AREA_HEIGHT PRINCESS_HEIGHT/20
#define TROPHY_WIDTH 18
#define TROPHY_HEIGHT 20
#define STANDING_BARREL_WIDTH 19
#define STANDING_BARREL_HEIGHT 29


class Map {
public:
	Map(char* filename, SDL_Surface* screen, SDL_Surface* floor_tex, SDL_Surface* ladder_tex, SDL_Surface* trophy_tex, SDL_Surface* princess_tex, SDL_Surface* standing_barrel_tex, SDL_Surface* charset);

	char map_path[MAP_PATH_LENGTH];
	int unset_trophy;
	int set_ending;
	ObjectList upper_ladders;
	ObjectList ladders;
	ObjectList tiles;
	StaticObject* trophy;
	StaticObject* princess;
	Object* ending_area;
	ObjectList standing_barrels;

	void draw();
	~Map();
private:
	SDL_Surface* screen;
	SDL_Surface* charset;
	void load_map(char* filename, SDL_Surface* floor_tex, SDL_Surface* ladder_tex, SDL_Surface* trophy_tex, SDL_Surface* princess_tex, SDL_Surface* standing_barrel_tex);

};

#endif