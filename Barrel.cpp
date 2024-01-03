#include "Barrel.h"

int Barrel::on_ground(Map* map) {
	for (int i = 0; i < map->tiles.get_size(); i++) {
		if (isOn(map->tiles.get(i))) {
			return 1;
		}
	}
	return 0;

}

void Barrel::barrel_gravity(Map* map, double delta) {
	if (on_ground(map)) {
			return;
	}
	move(0, GRAVITY*delta);
	jump_hitbox->move(0, GRAVITY*delta);
}

void Barrel::update(Map* map, double delta) {
	if (!on_ground(map) && !change_direction && x>=0) {
		vector *= -1;
		change_direction = 1;
	}
	else if (on_ground(map) && change_direction) {
		change_direction = 0;
	}

	if (on_ground(map)) {
		move(vector * BARREL_SPEED*delta, 0);
		jump_hitbox->move(vector * BARREL_SPEED*delta, 0);
	}
}

int Barrel::isOut() { //mozna do object -> zmienic scope na private
	if (x >= screen->w || x<=0) {
		return 1;
	}
	return 0;
}
