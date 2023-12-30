#include "Map.h"

Map::Map(char* filename, SDL_Surface* screen, SDL_Surface* floor_tex, SDL_Surface* ladder_tex) {
	this->screen = screen;
	load_map(filename, floor_tex, ladder_tex);
}

void Map::load_map(char* filename, SDL_Surface* floor_tex, SDL_Surface* ladder_tex) {
	FILE* f;
	f = fopen(filename, "r");

	if (f == NULL) {
		exit(1);
	}

	int map[MAP_HEIGHT][MAP_WIDTH];

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			fscanf(f, "%d ", &map[i][j]);
		}
	}

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			switch (map[i][j]) {
			case 1:
				tiles.add(new Floor(j * FLOOR_SIZE, i * FLOOR_SIZE + (screen->h - MAP_HEIGHT * FLOOR_SIZE), floor_tex, screen));
				break;
			case 2:
				ladders.add(new Ladder(j * LADDER_SIZE, i * LADDER_SIZE + (screen->h - MAP_HEIGHT * FLOOR_SIZE), ladder_tex, screen));
				break;
			}
		}
	}
}

void Map::draw() {
	for (int i = 0; i < tiles.get_size(); i++) {
		tiles.get(i)->draw();
	}
	for (int i = 0; i < ladders.get_size(); i++) {
		ladders.get(i)->draw();
	}
}