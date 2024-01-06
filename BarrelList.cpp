#include "BarrelList.h"

BarrelList::BarrelList() {
	size = 0;
	barrels = new Barrel * [size];
}

void BarrelList::add(Barrel* barrel) {
	Barrel** barrels_ext = new Barrel * [size + 1];
	for (int i = 0; i < size; i++) {
		barrels_ext[i] = barrels[i];
	}
	barrels_ext[size] = barrel;
	size++;
	delete[] barrels;
	barrels = barrels_ext;
}

void BarrelList::remove(Barrel * barrel) { //przesunac elementy o jeden do tylu
	delete[] barrel;
	size--;

}

int BarrelList::get_size() {
	return size;
}

Barrel* BarrelList::get(int i) {
	return barrels[i];
}

BarrelList::~BarrelList() {
	for (int i = 0; i < size; i++) {
		delete barrels[i];
	}
	delete[] barrels;
}