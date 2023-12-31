#include "Barrel.h"

int Barrel::on_ground(Map* map) {
	for (int i = 0; i < map->tiles.get_size(); i++) {
		if (isOn(map->tiles.get(i))) { // isCollision(map->tiles.get(i)) || 
			return 1;
		}
	}
	return 0;

}