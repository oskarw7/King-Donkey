#ifndef ANIMATION_H

#define ANIMATION_H

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

class Animation {
public:
	Animation(SDL_Surface* sprite, int f_width);
	void draw_frame(SDL_Surface* screen, int x, int y);
	

private:
	int frame_index;
	int frame_count;
	int f_width;
	SDL_Surface* sprite;
	SDL_Rect rect;

	void next_frame();
};

#endif