#include "ObjectList.h"

ObjectList::ObjectList() {
	size = 0;
	objects = new StaticObject*[size];
}

void ObjectList::add(StaticObject* object) {
	StaticObject** objects_extended = new StaticObject*[size + 1];
	for (int i = 0; i < size; i++) {
		objects_extended[i] = objects[i];
	}
	objects_extended[size] = object;
	size++;
	delete[] objects;
	objects = objects_extended;
}

int ObjectList::get_size() {
	return size;
}

StaticObject* ObjectList::get(int i) {
	return objects[i];
}

ObjectList::~ObjectList() {
	for (int i = 0; i < size; i++) {
		delete objects[i];
	}
	delete[] objects;
}