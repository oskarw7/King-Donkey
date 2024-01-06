#include "DonkeyKong.h"

void DonkeyKong::draw(double time) {
	animation->draw_frame(screen, x, y, time);
}

int DonkeyKong::get_frame_index() {
	if (animation->get_index() == 0)
		return 0;
	else if (animation->get_index() == 2)
		return 2;
	return -1;
		
}

DonkeyKong::~DonkeyKong() {
	delete animation;
	SDL_FreeSurface(texture);
}