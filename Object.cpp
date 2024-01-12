#include "Object.h"
Object::Object(double x, double y, double width, double height, SDL_Surface* screen) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->screen = screen;
}

//sprawdza kolizje
int Object::isCollision(Object* a) {
	if ((y < a->y + a->height) && (y + height > a->y) && (x < a->x + a->width) && (x + width > a->x)) {
		return 1;
	}
	return 0;
}

//sprawdza ograniczona kolizje (do drabin)
int Object::isTierceCollision(Object* a) {
	if ((y < a->y + a->height) && (y + height > a->y) && ((x < a->x + a->width / 3) && (x + width / 3 > a->x))) {
		return 1;
	}
	return 0;
}

//sprawdza czy obiekt jest na innym obiekcie
int Object::isOn(Object* a) {
	if (((y + height - a->y >= 0) && (y + height - a->y <= set_refresh_margin())) && (x < a->x + a->width) && (x + width > a->x)) {
		return 1;
	}
	return 0;
}

//sprawdza ograniczona kolizje gorna (do drabin)
int Object::isTierceOn(Object* a) {
	if (((y + height - a->y >= 0) && (y + height - a->y <= set_refresh_margin())) && (x < a->x + a->width / 3) && (x + width / 3 > a->x)) {
		return 1;
	}
	return 0;
}

//sprawdza czy obiekt jest w obszarze (do duzych predkosci/niskich fps)
int Object::check_broad_area(Object* a) {
	if ((y <= a->y + a->height) && (y + height >= a->y) && (x < a->x + a->width) && (x + width > a->x)) {
		return 1;
	}
	return 0;
}

//ustawia prog bledu wynikajacy z niskiej predkosci/niskich fps na podstawie grawitacji
double Object::set_refresh_margin() {
	double fraction;
	if (modf(GRAVITY, &fraction) == 0)
		return GRAVITY/100 + 1;
	else
		return ceil(GRAVITY/100);
}

//wyswietla blad ladowania obrazka
void Object::load_error(char* path) {
	printf("SDL_LoadBMP(%s) error: %s\n", path, SDL_GetError());
	exit(1);
}

//przesuwa obiekt
void Object::move(double mx, double my) {
	x += mx;
	y += my;
}

Object::~Object() {
	SDL_FreeSurface(screen);
}