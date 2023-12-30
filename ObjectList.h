#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "Object.h"

class ObjectList {
public:
	ObjectList();

	void add(Object* object);

	int get_size();
	Object* get(int i);

private:
	int size;
	Object** objects;
};

#endif // !OBJECT_LIST_H

