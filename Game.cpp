#include "Game.h"
#define TITLE "King Donkey"
#define CHARSET_PATH "./cs8x8.bmp"
#define PLAYER_PATH "./player.bmp"


Game::Game() {
	init_screen();
	load_graphics();
	SDL_ShowCursor(SDL_DISABLE);

	player = new Player(100, 100, player_tex, screen);

	start();
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

		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				key_press(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				etiSpeed = 1.0;
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

	/*
	SDL_FillRect(screen, NULL, czarny);
	DrawSurface(screen, eti,
		SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3,
		SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3);
	*/
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

	player->draw();
	/*
	sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

	sprintf(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);
	*/
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

	}
	else if (key == SDLK_DOWN) {

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