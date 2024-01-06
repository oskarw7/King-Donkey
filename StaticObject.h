#ifndef STATIC_OBJECT_H

#define STATIC_OBJECT_H
	
#include "Object.h"

class StaticObject : public Object {
public:
	StaticObject(int x, int y, int width, int height, SDL_Surface* texture, SDL_Surface* screen) : Object(x, y, width, height, screen) {
		this->texture = texture;
	};
	void draw();
private:
	SDL_Surface* texture;
};

#endif