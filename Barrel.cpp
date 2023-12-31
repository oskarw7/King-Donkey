#include "Barrel.h"

int Barrel::on_ground(Map* map) {
	for (int i = 0; i < map->tiles.get_size(); i++) {
		if (isOn(map->tiles.get(i))) {
			return 1;
		}
	}
	return 0;

}

void Barrel::barrel_gravity(Map* map) {
	if (on_ground(map)) {
			return;
		}
		move(0, GRAVITY);
}

void Barrel::update(Map* map) {
	if (!on_ground(map) && !change_direction && x>=0) {
		vector *= -1;
		change_direction = 1;
	}
	else if (!on_ground(map) && change_direction) {
		change_direction = 0;
	}

	move(vector*BARREL_SPEED, 0);
}

int Barrel::isOut() { //mozna do object -> zmienic scope na private
	if (x >= screen->h || x<=0) {
		return 1;
	}
	return 0;
}

void Barrel::move(int mx, int my) {
	x += mx;
	y += my;
	//beczka odbija sie od lewej sciany
}