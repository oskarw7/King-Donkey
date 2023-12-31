#ifndef BARRELS_LIST_H

#define BARRELS_LIST_H

#include "Barrel.h"

class BarrelList {
public:
	BarrelList();

	void add(Barrel* object);
	int get_size();
	Barrel* get(int i);
	void remove(Barrel* object);
private:
	int size;
	Barrel** barrels;
};

#endif