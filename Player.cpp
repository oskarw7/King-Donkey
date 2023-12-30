#include "Player.h"

int Player::on_ladder(Map* map) {
	for (int i = 0; i < map->ladders.get_size(); i++) {
		if (isCollision(map->ladders.get(i))) {
			return 1;
		}
	}
	return 0;
	
}


int Player::on_ground(Map* map) {
	for (int i = 0; i < map->tiles.get_size(); i++) {
		if (isCollision(map->tiles.get(i))) {
			return 1;
		}
	}
	return 0;

}