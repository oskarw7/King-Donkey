#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "StaticObject.h"

class ObjectList {
public:
	ObjectList();

	void add(StaticObject* object);

	int get_size();
	StaticObject* get(int i);
	~ObjectList();
private:
	int size;
	StaticObject** objects;
};

#endif // !OBJECT_LIST_H

