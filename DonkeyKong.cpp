#include "DonkeyKong.h"

void DonkeyKong::draw(double time) {
	animation->draw_frame(screen, x, y, time);
}

//zwroc indeks ostatniej lub srodkowej klatki animacji, w przeciwnym wypadku -1
int DonkeyKong::get_frame_index() {
	if (animation->get_index() == 2)
		return 2;
	else if (animation->get_index() == 1)
		return 1;
	return -1;
		
}

DonkeyKong::~DonkeyKong() {
	delete animation;
	SDL_FreeSurface(texture);
}