#include "Animation.h"

Animation::Animation(SDL_Surface* sprite, int f_width) {
	this->f_width = f_width;
	frame_count = sprite->w / f_width;
	this->sprite = sprite;
	rect = { 0, 0, f_width, sprite->h };
	frame_index = 0;
}

void Animation::next_frame() {
	frame_index++;
	if (frame_index >= frame_count) {
		frame_index = 0;
	}
}

void Animation::draw_frame(SDL_Surface* screen, int x, int y) {
	rect.x = frame_index * f_width;
	SDL_Rect position = { x, y, f_width, sprite->h };
	SDL_BlitSurface(sprite, &rect, screen, &position);
	next_frame();
}

