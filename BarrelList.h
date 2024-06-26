#ifndef BARRELS_LIST_H

#define BARRELS_LIST_H

#include "Barrel.h"

class BarrelList {
public:
	BarrelList();

	void add(Barrel* object);
	int get_size();
	Barrel* get(int i);
	void remove_first();
	void remove_all();
	~BarrelList();
private:
	int size;
	Barrel** barrels;
};

#endif