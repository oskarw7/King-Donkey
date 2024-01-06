#include "ObjectList.h"

ObjectList::ObjectList() {
	size = 0;
	objects = new StaticObject*[size];
}

void ObjectList::add(StaticObject* object) {
	StaticObject** objects_ext = new StaticObject*[size + 1];
	for (int i = 0; i < size; i++) {
		objects_ext[i] = objects[i];
	}
	objects_ext[size] = object;
	size++;
	delete[] objects;
	objects = objects_ext;
}

int ObjectList::get_size() {
	return size;
}

StaticObject* ObjectList::get(int i) {
	return objects[i];
}