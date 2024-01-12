#include "BarrelList.h"

BarrelList::BarrelList() {
	size = 0;
	barrels = new Barrel * [size];
}

void BarrelList::add(Barrel* barrel) {
	Barrel** barrels_extended = new Barrel * [size + 1];
	for (int i = 0; i < size; i++) {
		barrels_extended[i] = barrels[i];
	}
	barrels_extended[size] = barrel;
	size++;
	delete[] barrels;
	barrels = barrels_extended;
}

void BarrelList::remove_first() {
	delete barrels[0];
	for (int i = 0; i < size - 1; i++) {
		barrels[i] = barrels[i + 1];
	}
	size--;
	Barrel** barrels_decreased = new Barrel * [size];
	for(int i=0; i<size; i++)
		barrels_decreased[i] = barrels[i];
	delete[] barrels;
	barrels = barrels_decreased;
}

void BarrelList::remove_all() {
	for (int i = 0; i < size; i++) {
		delete barrels[i];
	}
	delete[] barrels;
	size = 0;
	barrels = new Barrel * [size];
}

int BarrelList::get_size() {
	return size;
}

Barrel* BarrelList::get(int i) {
	return barrels[i];
}

BarrelList::~BarrelList() {
	for (int i = 0; i < size; i++) {
		delete barrels[i]->animations.falling;
		delete barrels[i]->animations.rolling;
		delete barrels[i]->current_animation;
		delete barrels[i]->texture;
		delete barrels[i]->rolling_tex;
		delete barrels[i]->falling_tex;
		delete barrels[i];
	}
	delete[] barrels;
}