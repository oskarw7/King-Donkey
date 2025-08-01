#include "Map.h"

Map::Map(char* filename, SDL_Surface* screen, SDL_Surface* floor_tex, SDL_Surface* floor2_tex, SDL_Surface* floor3_tex, SDL_Surface* ladder_tex, SDL_Surface* trophy_tex, SDL_Surface* princess_tex, SDL_Surface* standing_barrel_tex, SDL_Surface* charset) {
	this->screen = screen;
	this->charset = charset;
	this->unset_trophy = 0;
	this->set_ending = 0;
	strcpy(this->map_path, filename);
	load_map(filename, floor_tex, floor2_tex, floor3_tex, ladder_tex, trophy_tex, princess_tex, standing_barrel_tex);
}

//ladowanie mapy z pliku, liczba odpowiada za typ obiektu
void Map::load_map(char* filename, SDL_Surface* floor_tex, SDL_Surface* floor2_tex, SDL_Surface* floor3_tex, SDL_Surface* ladder_tex, SDL_Surface* trophy_tex, SDL_Surface* princess_tex, SDL_Surface* standing_barrel_tex) {
	int map_width, map_height;
	FILE* f;
	f = fopen(filename, "r");
	if (f == NULL)
		exit(1);
	fscanf(f, "%d %d ", &map_height, &map_width);
	int** map = new int* [map_height];
	for (int i = 0; i < map_height; i++) {
		map[i] = new int[map_width];
	};
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			fscanf(f, "%d ", &map[i][j]);
		}
	}
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			switch (map[i][j]) {
			case 1:
				tiles.add(new StaticObject(j * FLOOR_SIZE, i * FLOOR_SIZE + (screen->h - map_height * FLOOR_SIZE), FLOOR_SIZE, FLOOR_SIZE, floor_tex, screen));
				break;
			case 2:
				ladders.add(new StaticObject(j * LADDER_SIZE, i * LADDER_SIZE + (screen->h - map_height * LADDER_SIZE), LADDER_SIZE, LADDER_SIZE, ladder_tex, screen));
				break;
			case 3:
				upper_ladders.add(new StaticObject(j * FLOOR_SIZE, i * FLOOR_SIZE + (screen->h - map_height * FLOOR_SIZE), LADDER_SIZE, LADDER_SIZE, ladder_tex, screen));
				break;
			case 4:
				trophy = new StaticObject(j * FLOOR_SIZE, i * FLOOR_SIZE + (screen->h - map_height * FLOOR_SIZE) + 5, TROPHY_WIDTH, TROPHY_HEIGHT, trophy_tex, screen);
				break;
			case 5:
				princess = new StaticObject(j * FLOOR_SIZE, i * FLOOR_SIZE + (screen->h - map_height * FLOOR_SIZE) + 5, PRINCESS_WIDTH, PRINCESS_HEIGHT, princess_tex, screen);
				ending_area = new Object(j * FLOOR_SIZE, i * FLOOR_SIZE + (screen->h - map_height * FLOOR_SIZE) + 5, ENDING_AREA_WIDTH, ENDING_AREA_HEIGHT, NULL);
				break;
			case 6:
				standing_barrels.add(new StaticObject(j * FLOOR_SIZE, i * FLOOR_SIZE + (screen->h - map_height * FLOOR_SIZE) + 7, STANDING_BARREL_WIDTH, STANDING_BARREL_HEIGHT, standing_barrel_tex, screen));
				break;
			case 7:
				tiles.add(new StaticObject(j * FLOOR_SIZE, i * FLOOR_SIZE + (screen->h - map_height * FLOOR_SIZE), FLOOR_SIZE, FLOOR_SIZE, floor2_tex, screen));
				break;
			case 8:
				tiles.add(new StaticObject(j * FLOOR_SIZE, i * FLOOR_SIZE + (screen->h - map_height * FLOOR_SIZE), FLOOR_SIZE, FLOOR_SIZE, floor3_tex, screen));
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
	for (int i = 0; i < standing_barrels.get_size(); i++) {
		standing_barrels.get(i)->draw();
	}

	if (unset_trophy != 1)
		trophy->draw();

	princess->draw();
	if (set_ending) {
		char text[128];
		sprintf(text, "Congratulations! Come closer to the Princess.");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 70, text, charset);
	}
}

void Map::reset() {
	unset_trophy = 0;
	set_ending = 0;
}

Map::~Map() {
	delete trophy;
	delete princess;
	delete ending_area;
}