#ifndef MAP_H
#define MAP_H

#include "Floor.h"
#include "Ladder.h"
#include "ObjectList.h"

#include<stdio.h>
#include <iostream>

#define MAP_HEIGHT 17
#define MAP_WIDTH 25

class Map {
public:
	Map(char* filename, SDL_Surface* screen, SDL_Surface* floor_tex, SDL_Surface* ladder_tex);

	ObjectList ladders;
	ObjectList tiles;

	void draw();
	
private:
	SDL_Surface* screen;
	void load_map(char* filename, SDL_Surface* floor_tex, SDL_Surface* ladder_tex);

};

#endif