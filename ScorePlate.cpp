#include "ScorePlate.h"

void ScorePlate::set_new_plate(SDL_Surface* texture, double time) {
	this->isShown = 1;
	this->start_time = time;
	this->current_score_plate = texture;
}

void ScorePlate::check_draw(int x, int y, double time) {
	if (current_score_plate != NULL && isShown && (time - start_time <= SCORE_PLATE_DURATION)) {
		DrawSurface(screen, current_score_plate, x + SCORE_PLATE_WIDTH / 2 - 10, y + SCORE_PLATE_HEIGHT / 2 - 40);
	}
	else if (start_time != 0 && time - start_time > SCORE_PLATE_DURATION) {
		isShown = 0;
		current_score_plate = NULL;
	}
}
