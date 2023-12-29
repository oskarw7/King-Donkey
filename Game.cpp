#include "Game.h"
#define TITLE "King Donkey"
#define CHARSET_PATH "./cs8x8.bmp"
#define PLAYER_PATH "./player.bmp"
#define FLOOR_PATH "./floor.bmp"
#define LADDER_PATH	"./ladder.bmp"
#define FILENAME "./map.txt"


Game::Game() {
	init_screen();
	load_graphics();
	SDL_ShowCursor(SDL_DISABLE);

	player = new Player(SCREEN_WIDTH-PLAYER_SIZE, SCREEN_HEIGHT-2*PLAYER_SIZE, player_tex, screen);

	load_map();

	start();
}

void Game::load_map() {
	FILE* f;
	f = fopen(FILENAME, "r");

	if (f == NULL) {
		exit(1);
	}

	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLS; j++) {
			fscanf(f, "%d ", &map[i][j]);
		}
	}

	int k = 0, l = 0;
	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLS; j++) {
			switch (map[i][j]) {
				case 1:
					tiles[k] = new Floor(j * FLOOR_SIZE, i * FLOOR_SIZE + 110, floor_tex, screen);
					k++;
					break;
				case 2:
					ladders[l] = new Ladder(j * LADDER_SIZE, i * LADDER_SIZE + 110, ladder_tex, screen);
					l++;
			}
		}
	}
}

void Game::init_screen() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		exit(1);
	}

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
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
	t1 = SDL_GetTicks();

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	distance = 0;
	etiSpeed = 1;

	while (!quit) {
		
		t2 = SDL_GetTicks();

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		delta = (t2 - t1) * 0.001;
		t1 = t2;

		worldTime += delta;

		distance += etiSpeed * delta;

		render();

		update();

		gravity(); //TODO gdzie wywolac, bug pod drabina, wbija w ziemie

		// obs³uga zdarzeñ
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				key_press(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				
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

void Game::render() {
	
	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	//SDL_FillRect(screen, NULL, czarny);

	fpsTimer += delta;
	if (fpsTimer > 0.5) {
		fps = frames * 2;
		frames = 0;
		fpsTimer -= 0.5;
	};

	// tekst informacyjny / info text
	DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, czerwony, czarny);
	DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski);

	sprintf(text, "Czas trwania: %.1lf s", worldTime);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

	sprintf(text, "Wykonane punkty:");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

	draw_map();

	player->draw();
}

void Game::draw_map() {
	for (int i = 0; i < TILES_COUNT; i++) {
		tiles[i]->draw();
	}
	for (int i = 0; i < LADDER_COUNT; i++) {
		ladders[i]->draw();
	}
}

void Game::update() {
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//		SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
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

void Game::key_press(SDL_Keycode key) {
	if (key == SDLK_ESCAPE) {
		quit = 1;
	}
	else if (key == SDLK_UP) {
		for (int i = 0; i < LADDER_COUNT; i++) {
			if (player->isCollision(ladders[i])) {
				player->move(0, -player->speed);
			}
		}
	}
	else if (key == SDLK_DOWN) {
		for (int i = 0; i < LADDER_COUNT; i++) {
			if (player->isCollision(ladders[i])) {
				player->move(0, player->speed);
			}
		}
	}
	else if (key == SDLK_LEFT) {
		player->move(-player->speed, 0);
	}
	else if (key == SDLK_RIGHT) {
		player->move(player->speed, 0);
	}
	else if (key == SDLK_n) {

	}
}

void Game::gravity() {
	player->isFalling = 1;
	for (int i = 0; i < TILES_COUNT; i++) {
		for (int j = 0; j < LADDER_COUNT; j++) {
			if (player->isCollision(tiles[i]) || player->isCollision(ladders[j])) {
				player->isFalling = 0;
			}
		}
	}
	if (player->isFalling == 1) {
		player->move(0, GRAVITY);
	}
}