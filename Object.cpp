#include "Object.h"
Object::Object(int x, int y, int width, int height, SDL_Surface* screen) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->frame_width = frame_width;
	this->screen = screen;
}

int Object::isCollision(Object* a) {
	if ((y < a->y + a->height) && (y + height > a->y) && (x < a->x + a->width) && (x + width > a->x)) {
		return 1;
	}
	return 0;
}

int Object::isQuarterCollision(Object* a) {
	if ((y < a->y + a->height) && (y + height > a->y) && (x < a->x + a->width / 3) && (x + width / 3 > a->x)) {
		return 1;
	}
	return 0;
}

int Object::isOn(Object* a) {
	if (((y + height - a->y >= 0) && (y + height - a->y <= set_refresh_margin())) && (x < a->x + a->width) && (x + width > a->x)) {
		return 1;
	}
	return 0;
}

int Object::isTierceOn(Object* a) {
	if (((y + height - a->y >= 0) && (y + height - a->y <= set_refresh_margin())) && (x < a->x + a->width / 4) && (x + width / 4 > a->x)) {
		return 1;
	}
	return 0;
}

int Object::check_broad_area(Object* a) {
	if ((y <= a->y + a->height) && (y + height >= a->y) && (x < a->x + a->width) && (x + width > a->x)) {
		return 1;
	}
	return 0;
}

double Object::set_refresh_margin() {
	double fraction;
	if (modf(GRAVITY, &fraction) == 0)
		return GRAVITY/100 + 1;
	else
		return ceil(GRAVITY/100);
}

void Object::move(int mx, int my) {
	x += mx;
	y += my;
}

Object::~Object() {
	delete screen;
}