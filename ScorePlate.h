#ifndef SCORE_PLATE_H

#define SCORE_PLATE_H

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "utils.h"

#define	PLUS100_PATH "./Assets/plus100.bmp"
#define	PLUS300_PATH "./Assets/plus300.bmp"
#define SCORE_PLATE_WIDTH 48		//pixele
#define SCORE_PLATE_HEIGHT 15		//pixele
#define SCORE_PLATE_DURATION 1.0	//sekundy

class ScorePlate {
public:
	ScorePlate(SDL_Surface* screen){
		this->current_score_plate = NULL;
		this->start_time = 0.0;
		this->isShown = 0;
		this->screen = screen;
	};
	void set_new_plate(SDL_Surface* texture, double time);
	void check_draw(int x, int y, double time);
	void reset();

	int isShown; //czy wyswietlac
	double start_time; //czas rozpoczecia wyswietlania
	SDL_Surface* current_score_plate;
	~ScorePlate();
private:
	SDL_Surface* screen;
};

#endif
