#ifndef MAP_H
#define MAP_H

#include "Object.h"
#include "Floor.h"
#include "Ladder.h"
#include "ObjectList.h"
#include "utils.h"

#include <string.h>
#include <stdio.h>

#define MAP_HEIGHT 20
#define MAP_WIDTH 25
#define MAP_PATH_LENGTH 17
#define TROPHY_WIDTH 18
#define TROPHY_HEIGHT 20

class Map {
public:
	Map(char* filename, SDL_Surface* screen, SDL_Surface* floor_tex, SDL_Surface* ladder_tex, SDL_Surface* trophy_tex, SDL_Surface* charset);

	char map_path[MAP_PATH_LENGTH];
	int unset_trophy;
	int set_ending;
	ObjectList upper_ladders;
	ObjectList ladders;
	ObjectList tiles;
	Object* trophy;

	void draw();
	
private:
	SDL_Surface* screen;
	SDL_Surface* charset;
	void load_map(char* filename, SDL_Surface* floor_tex, SDL_Surface* ladder_tex, SDL_Surface* trophy_tex);

};

#endif