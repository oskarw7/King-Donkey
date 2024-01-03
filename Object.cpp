#include "Object.h"
Object::Object(int x, int y, int width, int height, SDL_Surface* texture, SDL_Surface* screen) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	this->texture = texture;
	this->screen = screen;
}

void Object::draw() {
	DrawSurface(screen, texture, x+width/2, y+width/2);
}

int Object::isCollision(Object* a) {
	if ((y < a->y + a->height) && (y + height > a->y) && (x < a->x + a->width) && (x + width > a->x)) {
		return 1;
	}
	return 0;
}

int Object::isOn(Object* a) {
	if (((y + height - a->y >= 0) && (y + height - a->y <=	set_refresh_margin())) && (x < a->x + a->width) && (x + width > a->x)) {
		return 1;
	}
	return 0;
}

double Object::set_refresh_margin() {
	double fraction;
	if (modf(GRAVITY, &fraction) == 0)
		return GRAVITY + 1;
	else
		return ceil(GRAVITY);
}

void Object::move(int mx, int my) {
	x += mx;
	y += my;
}