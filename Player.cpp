#include "Player.h"

int Player::on_ladder(Map* map) {
	for (int i = 0; i < map->ladders.get_size(); i++) {
		if (isCollision(map->ladders.get(i))) {
			return 1;
		}
	}
	for (int i = 0; i < map->upper_ladders.get_size(); i++) {
		if (isCollision(map->upper_ladders.get(i))) {
			return 1;
		}
	}
	return 0;
	
}


int Player::on_ground(Map* map) {
	for (int i = 0; i < map->tiles.get_size(); i++) {
		if (isOn(map->tiles.get(i))) { 
			return 1;
		}
	}
	return 0;

}

int Player::touch_tile(Map* map) {
	for (int i = 0; i < map->tiles.get_size(); i++) {
		if (isCollision(map->tiles.get(i))) {
			return 1;
		}
	}
	return 0;

}

int Player::above_ladder(Map* map) {
	for (int i = 0; i < map->upper_ladders.get_size(); i++) {
		if (isOn(map->upper_ladders.get(i))) {
			return 1;
		}
	}
	return 0;

}

void Player::player_move(int mx, int my) {
	x += mx;
	y += my;
	if (x < 0) {
		x = 0;
	}
	else if (x > screen->w - width) {
		x = screen->w - width;
	}

	if (y < 0) {
		y = 0;
	}
	else if (y > screen->h - FLOOR_SIZE - height) {
		y = screen->h - FLOOR_SIZE - height;
	}
}
