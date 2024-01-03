#include "Map.h"

Map::Map(char* filename, SDL_Surface* screen, SDL_Surface* floor_tex, SDL_Surface* ladder_tex, SDL_Surface* trophy_tex, SDL_Surface* charset) {
	this->screen = screen;
	this->charset = charset;
	this->unset_trophy = 0;
	this->set_ending = 0;
	strcpy(this->map_path, filename);
	load_map(filename, floor_tex, ladder_tex, trophy_tex);
}

void Map::load_map(char* filename, SDL_Surface* floor_tex, SDL_Surface* ladder_tex, SDL_Surface* trophy_tex) {
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
				ladders.add(new Ladder(j * LADDER_SIZE, i * LADDER_SIZE + (screen->h - MAP_HEIGHT * LADDER_SIZE), ladder_tex, screen));
				break;
			case 3:
				upper_ladders.add(new Floor(j * FLOOR_SIZE, i * FLOOR_SIZE + (screen->h - MAP_HEIGHT * FLOOR_SIZE), ladder_tex, screen));
				break;
			case 4:
				trophy = new Object(j * FLOOR_SIZE, i * FLOOR_SIZE + (screen->h - MAP_HEIGHT * FLOOR_SIZE), TROPHY_WIDTH, TROPHY_HEIGHT, trophy_tex, screen);
				break;
			}
		}
	}
	fclose(f);
}

void Map::draw() {
	for (int i = 0; i < tiles.get_size(); i++) {
		tiles.get(i)->draw();
	}
	for (int i = 0; i < ladders.get_size(); i++) {
		ladders.get(i)->draw();
	}
	for (int i = 0; i < upper_ladders.get_size(); i++) {
		upper_ladders.get(i)->draw();
	}
	if(unset_trophy!=1)
		trophy->draw();
	if (set_ending) {
		char text[128];
		sprintf(text, "Gratulacje! Podejdz do ksiezniczki.");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 70, text, charset);
	}
}