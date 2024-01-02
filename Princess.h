#ifndef  PRINCESS_H

#define PRINCESS_H

#include "Object.h"

#define PRINCESS_X 127
#define PRINCESS_Y 83
#define PRINCESS_WIDTH 23
#define PRINCESS_HEIGHT 32
#define ENDING_AREA_WIDTH 32*3
#define ENDING_AREA_HEIGHT PRINCESS_HEIGHT/20


class Princess : public Object {
public:
	Princess(int x, int y, SDL_Surface* texture, SDL_Surface* screen) : Object(x, y, PRINCESS_WIDTH, PRINCESS_HEIGHT, texture, screen) {
		ending_area = new Object(PRINCESS_X, PRINCESS_Y, ENDING_AREA_WIDTH, ENDING_AREA_HEIGHT, NULL, NULL);
	};
	Object* ending_area;
};
#endif // ! PRINCESS_H
