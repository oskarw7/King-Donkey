#ifndef ANIMATION_H

#define ANIMATION_H

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

class Animation {
public:
	Animation(SDL_Surface* sprite, int f_width, double time_interval);
	void draw_frame(SDL_Surface* screen, int x, int y, double time);
	void next_frame();
	int get_index() { return frame_index; };

private:
	int frame_index;
	int frame_count;
	int f_width;
	SDL_Surface* sprite;
	SDL_Rect rect;
	double time_interval;
	double last_time;
};

#endif