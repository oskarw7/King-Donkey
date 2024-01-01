#include "Game.h"

Game::Game() {
	init_screen();
	load_graphics();
	SDL_ShowCursor(SDL_DISABLE);

	player = new Player(SCREEN_WIDTH-PLAYER_SIZE, SCREEN_HEIGHT-2*PLAYER_SIZE, player_tex, screen);

	map = new Map(MAP1_FILENAME, screen, floor_tex, ladder_tex);

	barrels.add(new Barrel(BARREL_START_X, BARREL_START_Y, barrel_tex, screen));

	quit = 0;

	game_started = 0;

	start();

}


void Game::init_screen() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		exit(1);
	}

	int rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		exit(1);
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, TITLE);

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::load_graphics() {
	charset = SDL_LoadBMP(CHARSET_PATH);
	if (charset == NULL) {
		load_error(charset, CHARSET_PATH);
	};
	SDL_SetColorKey(charset, true, 0x000000);

	player_tex = SDL_LoadBMP(PLAYER_PATH);
	if (player_tex == NULL) {
		load_error(player_tex, PLAYER_PATH);
	};

	floor_tex = SDL_LoadBMP(FLOOR_PATH);
	if (floor_tex == NULL) {
		load_error(floor_tex, FLOOR_PATH);
	}

	ladder_tex = SDL_LoadBMP(LADDER_PATH);
	if (ladder_tex == NULL) {
		load_error(ladder_tex, LADDER_PATH);
	}

	barrel_tex = SDL_LoadBMP(BARREL_PATH);
	if (barrel_tex == NULL) {
		load_error(barrel_tex, BARREL_PATH);
	}

	princess_tex = SDL_LoadBMP(PRINCESS_PATH);
	if (princess_tex == NULL) {
		load_error(princess_tex, PRINCESS_PATH);
	};
}

void Game::load_error(SDL_Surface* surface, char* path) {
	printf("SDL_LoadBMP(%s) error: %s\n", path, SDL_GetError());
	SDL_FreeSurface(surface);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	exit(1);
}

void Game::start() {
	int frames = 0;

	double t1 = SDL_GetTicks();
	double t2 = t1;
	double fpsTimer = 0;
	double fps = 0;
	double delta = 0;

	worldTime = 0;

	while (!quit) {

		manage_time(&delta, &t1, &t2, &worldTime, &fpsTimer, &fps, &frames);

		render();

		if (game_started) {
			if(fmod(worldTime, BARREL_FREQUENCY) < BARREL_TIME_MARGIN)
				barrels.add(new Barrel(BARREL_START_X, BARREL_START_Y, barrel_tex, screen));
			update();
		}

		// obs³uga zdarzeñ
		SDL_Keycode key;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				key = event.key.keysym.sym;
				if (key == SDLK_UP) {
					pk.up = 1;
				}
				else if (key == SDLK_DOWN) {
					pk.down = 1;
				}
				else if (key == SDLK_LEFT) {
					pk.left = 1;
				}
				else if (key == SDLK_RIGHT) {
					pk.right = 1;
				}
				else if (key == SDLK_SPACE) {
					pk.space = 1;
				} 
				else if (key == SDLK_n) {
					game_started = 1;
				}
				else if (key == SDLK_ESCAPE) {
					quit = 1;
				}
				else if (key == SDLK_7) {
					change_map();
				}
				break;

			case SDL_KEYUP:
				key = event.key.keysym.sym;

				if (key == SDLK_UP) {
					pk.up = 0;
				}
				else if (key == SDLK_DOWN) {
					pk.down = 0;
				}
				else if (key == SDLK_LEFT) {
					pk.left = 0;
				}
				else if (key == SDLK_RIGHT) {
					pk.right = 0;
				}
				else if (key == SDLK_SPACE) {
					pk.space = 0;
				}
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};
		frames++;
	};
	stop();
}

void Game::manage_time(double* delta, double* t1, double *t2, double* worldTime, double* fpsTimer, double* fps, int* frames) {
	// w tym momencie t2-t1 to czas w milisekundach,
	// jaki uplyna³ od ostatniego narysowania ekranu
	// delta to ten sam czas w sekundach
	*t2 = SDL_GetTicks();
	*delta = (*t2 - *t1) * 0.001;
	*t1 = *t2;

	if (game_started) {
		*worldTime += *delta;
	}

	*fpsTimer += *delta;
	if (*fpsTimer > 0.5) {
		*fps = *frames * 2;
		*frames = 0;
		*fpsTimer -= 0.5;
	};
}

void Game::render() {
	
	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	// tekst informacyjny
	DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, czerwony, czarny);
	DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 50, czerwony, niebieski);

	char* second_bind = "";
	if (!game_started) {
		second_bind = ", N - nowa gra";
	}
	sprintf(text, "ESC - wyjscie%s", second_bind);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

	sprintf(text, "Czas trwania: %.1lf s", worldTime);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

	sprintf(text, "Wykonane punkty:");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 42, text, charset);

	map->draw();

	for (int i = 0; i < barrels.get_size(); i++) {
		barrels.get(i)->draw();
	}

	player->draw();

	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//		SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}


void Game::update() {
	players_gravity();

	for (int i = 0; i < barrels.get_size(); i++)
		barrels.get(i)->barrel_gravity(map);

	int mx = 0, my = 0;
	if (pk.up) {
		if (player->on_ladder(map)) {
			my -= player->speed;
		}
	}
	else if (pk.down) {
		if (player->on_ladder(map)) {
			my += player->speed;
		}
	}
	else if (pk.left) {
		mx -= player->speed;
	}
	else if (pk.right) {
		mx += player->speed;
	}
	if (pk.space) {
		if (player->on_ground(map) || ((player->on_ladder(map) && player->touch_tile(map))))
			my -= JUMP_FORCE * GRAVITY; //rozbicie na parametry ruchu (x, v, a)
	}
	player->move(mx, my);

	for (int i = 0; i < barrels.get_size(); i++) {
		barrels.get(i)->update(map);
		if (barrels.get(i)->isOut()) {
			//barrels.remove(barrels.get(i));
		}
	}

	hit_barrel();
}

void Game::stop() {
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	exit(0);
}


void Game::players_gravity() {
	if (player->on_ladder(map) || player->on_ground(map)) {
		return;
	}
	player->move(0, GRAVITY);
}

void Game::hit_barrel() {
	for (int i = 0; i < barrels.get_size(); i++) {
		if (player->isCollision(barrels.get(i))) {
			printf("HIT!");
		}
	}
}

void Game::change_map() {
	if (strcmp(map->map_path, MAP1_FILENAME)==0) {
		printf("1");
		map = new Map(MAP2_FILENAME, screen, floor_tex, ladder_tex);
	}
	else if (strcmp(map->map_path, MAP2_FILENAME) == 0) {
		printf("2");
		map = new Map(MAP3_FILENAME, screen, floor_tex, ladder_tex);
	}
	else if (strcmp(map->map_path, MAP3_FILENAME) == 0) {
		printf("3");
		map = new Map(MAP1_FILENAME, screen, floor_tex, ladder_tex);
	}
	printf("xx");
}