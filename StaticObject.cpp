#include "StaticObject.h"

void StaticObject::draw() {
	DrawSurface(screen, texture, x+width/2, y+width/2);
}