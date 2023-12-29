#include "Object.h"
Object::Object(int x, int y, int width, int height, SDL_Surface* texture, SDL_Surface* screen) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->mid_x = x + width / 2;
	this->mid_y = y + height / 2;

	this->texture = texture;
	this->screen = screen;
}

void Object::draw() {
	DrawSurface(screen, texture, x+width/2, y+width/2);
}

int Object::isCollision(Object* a) {
	//if (abs(mid_x - a->mid_x) <= width / 2 + a->width / 2 && abs(mid_y - a->mid_y) <= height / 2 + a->height / 2) {
	//	std::cout << "xxxx";
	//	return 1;
	//}
	//return 0;
	if ((y < a->y + a->height) && (y + height > a->y) && (x < a->x + a->width) && (x + width > a->x)) {		//  < czy <=
		return 1;
	}
	return 0;
}

void Object::move(int mx, int my) {
	x += mx;
	y += my;
	if (x < 0) {
		x = 0;
	}
	else if (x > screen->w - width) {
		x = screen->w - width;
	}

	if (y < 0) {
		y = 0;
	}
	else if (y > screen->h - height) {
		y = screen->h - height;
	}
}