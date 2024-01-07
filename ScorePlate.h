#ifndef SCORE_PLATE_H

#define SCORE_PLATE_H

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "utils.h"

#define	PLUS100_PATH "./Assets/plus100.bmp"
#define	PLUS300_PATH "./Assets/plus300.bmp"
#define SCORE_PLATE_WIDTH 48
#define SCORE_PLATE_HEIGHT 15
#define SCORE_PLATE_DURATION 2.0

class ScorePlate {
public:
	ScorePlate(SDL_Surface* screen){
		this->current_score_plate = NULL;
		this->start_time = 0;
		this->isShown = 0;
		this->screen = screen;
	};
	void set_new_plate(SDL_Surface* texture, double time);
	void check_draw(int x, int y, double time);

	int isShown;
	int start_time;
	SDL_Surface* current_score_plate;
private:
	SDL_Surface* screen;
};

#endif
