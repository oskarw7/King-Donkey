#include "ObjectList.h"

ObjectList::ObjectList() {
	size = 0;
	objects = new Object*[size];
}

void ObjectList::add(Object* object) {
	Object** objects_ext = new Object*[size + 1];
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

Object* ObjectList::get(int i) {
	return objects[i];
}