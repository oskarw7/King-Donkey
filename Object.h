#ifndef OBJECT_H

#define OBJECT_H
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "utils.h"
#include <math.h>


#define	GRAVITY 450.0

class Object {
public:

	Object(double x, double y, double width, double height, SDL_Surface* screen);
	int isCollision(Object* a);
	int isQuarterCollision(Object* a);
	int isOn(Object* a);
	int isQuarterOn(Object* a);
	int check_broad_area(Object* a);
	void move(int mx, int my);
	int get_x() { return x; };
	int get_y() { return y; };
	int get_height() { return height; };
	int get_width() { return width; };
	virtual ~Object();
protected:
	double x;
	double y;
	double width;
	double height;
	int frame_width;
	SDL_Surface* screen;
private:
	double set_refresh_margin();
};


#endif