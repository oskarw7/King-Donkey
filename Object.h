#ifndef OBJECT_H

#define OBJECT_H
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "utils.h"
#include <math.h>

#define REFRESH_MARGIN 4
#define	GRAVITY 3.5

class Object {
public:

	Object(int x, int y, int width, int height, SDL_Surface* texture, SDL_Surface* screen);
	int isCollision(Object* a);
	int isOn(Object* a);
	void draw();
	void move(int mx, int my);

protected: //ex public (do isOut w barrel)
	int x;
	int y;
	int width;
	int height;
	SDL_Surface* texture;
	SDL_Surface* screen;
};


#endif