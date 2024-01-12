#include "Animation.h"

Animation::Animation(SDL_Surface* sprite, int frame_width, double time_interval) {
	this->frame_width = frame_width;
	frame_count = sprite->w / frame_width;
	this->sprite = sprite;
	rect = { 0, 0, frame_width, sprite->h };
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
	rect.x = frame_index * frame_width;
	SDL_Rect position = { x, y, frame_width, sprite->h };
	SDL_BlitSurface(sprite, &rect, screen, &position);
	if (time - last_time >= time_interval) {
		next_frame();
		last_time = time;
	}

}

void Animation::reset() {
	frame_index = 0;
}

Animation::~Animation() {
	SDL_FreeSurface(sprite);
}