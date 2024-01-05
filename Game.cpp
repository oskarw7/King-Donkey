#include "Game.h"

Game::Game() {
	init_screen();
	load_graphics();
	SDL_ShowCursor(SDL_DISABLE);

	player = new Player(SCREEN_WIDTH-PLAYER_WIDTH, SCREEN_HEIGHT-2*PLAYER_HEIGHT, player_tex, PLAYER_WIDTH, screen);

	map = new Map(MAP1_FILENAME, screen, floor_tex, ladder_tex, trophy_tex, princess_tex, standing_barrel_tex, charset);

	barrels.add(new Barrel(BARREL_START_X, BARREL_START_Y, barrel_tex, BARREL_WIDTH, screen));

	donkey_kong = new Object(KONG_START_X, KONG_START_Y, KONG_WIDTH, KONG_HEIGHT, donkey_kong_tex, KONG_WIDTH, screen);

	quit = 0;

	first_completed = 0;
	second_completed = 0;
	third_completed = 0;

	game_started = 0;
	game_paused = 0;

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

	standing_barrel_tex = SDL_LoadBMP(STANDING_BARREL_PATH);
	if (standing_barrel_tex == NULL) {
		load_error(standing_barrel_tex, STANDING_BARREL_PATH);
	}

	princess_tex = SDL_LoadBMP(PRINCESS_PATH);
	if (princess_tex == NULL) {
		load_error(princess_tex, PRINCESS_PATH);
	};

	trophy_tex = SDL_LoadBMP(TROPHY_PATH);
	if (trophy_tex == NULL) {
		load_error(trophy_tex, TROPHY_PATH);
	}

	heart_tex = SDL_LoadBMP(HEART_PATH);
	if (heart_tex == NULL) {
		load_error(heart_tex, HEART_PATH);
	}

	donkey_kong_tex = SDL_LoadBMP(DONKEY_KONG_PATH);
	if (donkey_kong_tex == NULL) {
		load_error(donkey_kong_tex, DONKEY_KONG_PATH);
	}
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
	double t2;
	double fpsTimer = 0;
	double fps = 0;
	double delta = 0;

	worldTime = 0;

	while (!quit) {

		manage_time(&delta, &t1, &t2, &worldTime, &fpsTimer, &fps, &frames);

		render();

		if (game_started) {
			update(delta*100);
		}

		// obs�uga zdarze�
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
				else if (key == SDLK_c && game_paused) {
					game_paused = 0;
					game_started = 1;
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
	// jaki uplyna� od ostatniego narysowania ekranu
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
		second_bind = ", N - new game";
	}

	sprintf(text, "ESC - quit%s", second_bind);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

	sprintf(text, "Gametime: %.1lf s", worldTime);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

	sprintf(text, "Implemented points:");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 42, text, charset);

	sprintf(text, "Score: %d", player->score);
	DrawString(screen, screen->w - strlen(text) * 8 - 10, 60, text, charset);

	map->draw();
	draw_lives();

	for (int i = 0; i < barrels.get_size(); i++) {
		barrels.get(i)->draw();
	}

	donkey_kong->draw();

	player->draw();

	if (game_paused) {
		SDL_FillRect(screen, NULL, czerwony);
		DrawRectangle(screen, SCREEN_WIDTH/8, SCREEN_HEIGHT/3, 6*SCREEN_WIDTH/8, SCREEN_HEIGHT/3, czerwony, czarny);
		sprintf(text, "You losed life. Do you want to continue?");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT/2 - 20, text, charset);
		sprintf(text, "C - CONTINUE");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2, text, charset);
		sprintf(text, "ESC - QUIT");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2 + 20, text, charset);
	}

	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//		SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}


void Game::update(double delta) {
	players_gravity(delta);

	for (int i = 0; i < barrels.get_size(); i++)
		barrels.get(i)->barrel_gravity(map, delta);

	int mx = 0, my = 0;
	if (pk.up) {
		if (player->on_ladder(map)) {
			my -= player->speed * delta;
		}
	}
	else if (pk.down) {
		if ((player->on_ladder(map) && !player->on_ground(map)) || player->above_ladder(map)) {
			my += player->speed * delta;
		}
	}
	else if (pk.left) {
		if(!player->on_ladder(map) || player->on_ground(map) || player->above_ladder(map))
			mx -= player->speed * delta;
	}
	else if (pk.right) {
		if (!player->on_ladder(map) || player->on_ground(map) || player->above_ladder(map))
			mx += player->speed * delta;
	}
	if (pk.space) {
		if ((player->on_ground(map) && !player->on_ladder(map)) || ((player->on_upper_ladder(map) && player->touch_tile(map))))
			my -= JUMP_FORCE * GRAVITY * delta; //rozbicie na parametry ruchu (x, v, a)
	}
	player->player_move(mx, my);

	for (int i = 0; i < barrels.get_size(); i++) {
		barrels.get(i)->update(map, delta);
		if (barrels.get(i)->isOut()) {
			//barrels.remove(barrels.get(i));
		}
	}

	hit_barrel();

	if (fmod(worldTime, BARREL_FREQUENCY) < BARREL_TIME_MARGIN)
		barrels.add(new Barrel(BARREL_START_X, BARREL_START_Y, barrel_tex, BARREL_WIDTH, screen));

	check_trophy();

	check_princess();
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

void Game::players_gravity(double delta) {
	if (player->on_ladder(map) || player->on_ground(map)) {
		return;
	}
	player->player_move(0, GRAVITY*delta);
}

void Game::hit_barrel() {
	for (int i = 0; i < barrels.get_size(); i++) {
		Barrel* barrel = barrels.get(i);
		if (player->isCollision(barrel) && barrel->player_hit == 0) {
			printf("HIT!");
			player->lives--;
			barrel->player_hit = 1;
			game_started = 0;
			game_paused = 1;
			player->player_move(SCREEN_WIDTH - PLAYER_WIDTH, SCREEN_HEIGHT - 2 * PLAYER_HEIGHT);
		}
		else if (player->isCollision(barrel->jump_hitbox) && barrel->player_hit == 0) {
			player->score+=100;
			barrel->player_hit = 1;
		}
		
	}
}

void Game::change_map() {
	if (strcmp(map->map_path, MAP1_FILENAME)==0) {
		map = new Map(MAP2_FILENAME, screen, floor_tex, ladder_tex, trophy_tex, princess_tex, standing_barrel_tex, charset);
	}
	else if (strcmp(map->map_path, MAP2_FILENAME) == 0) {
		map = new Map(MAP3_FILENAME, screen, floor_tex, ladder_tex, trophy_tex, princess_tex, standing_barrel_tex, charset);
	}
	else if (strcmp(map->map_path, MAP3_FILENAME) == 0) {
		map = new Map(MAP1_FILENAME, screen, floor_tex, ladder_tex, trophy_tex, princess_tex, standing_barrel_tex, charset);
	}
}

void Game::check_princess() {
	if (player->isCollision(map->ending_area)) {
		map->set_ending = 1;
	}
	if (player->isCollision(map->princess)) {
		printf("WIN!");
		if (first_completed==0 && strcmp(map->map_path, MAP1_FILENAME) == 0) {
			map = new Map(MAP2_FILENAME, screen, floor_tex, ladder_tex, trophy_tex, princess_tex, standing_barrel_tex, charset);
			player->score += 500;
			first_completed = 1;
		}
		else if (first_completed == 1 && second_completed==0 && strcmp(map->map_path, MAP2_FILENAME) == 0) {
			map = new Map(MAP3_FILENAME, screen, floor_tex, ladder_tex, trophy_tex, princess_tex, standing_barrel_tex, charset);
			player->score += 1000;
			second_completed = 1;
		}
		else if (first_completed == 1 && second_completed == 1 && third_completed==0 && strcmp(map->map_path, MAP3_FILENAME) == 0) {
			player->score += 1500;
			third_completed = 1;
			stop();
		}
		player->player_move(SCREEN_WIDTH - PLAYER_WIDTH, SCREEN_HEIGHT - 2 * PLAYER_HEIGHT	);
	}
}

void Game::check_trophy() {
	if (player->isCollision(map->trophy)) {
		delete[] map->trophy;
		player->score += 300;
		map->unset_trophy = 1;
	}
}

void Game::draw_lives() {
	for (int i = 0; i < player->lives; i++) {
		DrawSurface(screen, heart_tex, i * (HEART_WIDTH+5) + HEART_START_X, HEART_START_Y);
	}
}