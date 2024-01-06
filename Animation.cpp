#include "Animation.h"

Animation::Animation(SDL_Surface* sprite, int f_width, double time_interval) {
	this->f_width = f_width;
	frame_count = sprite->w / f_width;
	this->sprite = sprite;
	rect = { 0, 0, f_width, sprite->h };
	frame_index = 0;
	this->time_interval = time_interval;
	last_time = 0;
}

void Animation::next_frame() {
	frame_index++;
	if (frame_index >= frame_count) {
		frame_index = 0;
	}
}

void Animation::draw_frame(SDL_Surface* screen, int x, int y, double time) {
	rect.x = frame_index * f_width;
	SDL_Rect position = { x, y, f_width, sprite->h };
	SDL_BlitSurface(sprite, &rect, screen, &position);
	if (time - last_time >= time_interval) {
		next_frame();
		last_time = time;
	}

}

