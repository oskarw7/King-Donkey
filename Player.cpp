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

int Player::on_upper_ladder(Map* map) {
	for (int i = 0; i < map->upper_ladders.get_size(); i++) {
		if (isCollision(map->upper_ladders.get(i))) {
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

void Player::load_player_graphics() {
	walking_left_tex = SDL_LoadBMP(WALKING_LEFT_PATH);
	if (walking_left_tex == NULL) {
		//load_error(walking_left_tex, WALKING_LEFT_PATH);
		exit(1);
	};

	walking_right_tex = SDL_LoadBMP(WALKING_RIGHT_PATH);
	if (walking_right_tex == NULL) {
		//load_error(walking_right_tex, WALKING_RIGHT_PATH);
		exit(1);
	};

	climb_tex = SDL_LoadBMP(CLIMB_PATH);
	if (climb_tex == NULL) {
		//load_error(climb_tex, CLIMB_PATH);
		exit(1);
	};

	steady_climb_tex = SDL_LoadBMP(STEADY_CLIMB_PATH);
	if (steady_climb_tex == NULL) {
		//load_error(climb_tex, CLIMB_PATH);
		exit(1);
	};

	back_tex = SDL_LoadBMP(BACK_PATH);
	if (back_tex == NULL) {
		//load_error(climb_tex, CLIMB_PATH);
		exit(1);
	};


	standing_left_tex = SDL_LoadBMP(STANDING_LEFT_PATH);
	if (standing_left_tex == NULL) {
		//load_error(standing_left_tex, STANDING_LEFT_PATH);
		exit(1);
	};

	standing_right_tex = SDL_LoadBMP(STANDING_RIGHT_PATH);
	if (standing_right_tex == NULL) {
		//load_error(standing_right_tex, STANDING_RIGHT_PATH);
		exit(1);
	};

	jumping_left_tex = SDL_LoadBMP(JUMPING_LEFT_PATH);
	if (jumping_left_tex == NULL) {
		//load_error(jumping_left_tex, JUMPING_LEFT_PATH);
		exit(1);
	};

	jumping_right_tex = SDL_LoadBMP(JUMPING_RIGHT_PATH);
	if (jumping_right_tex == NULL) {
		//load_error(jumping_right_tex, JUMPING_RIGHT_PATH);
		exit(1);
	};

	animations.walking_left = new Animation(walking_left_tex, PLAYER_WIDTH, 0.2);
	animations.walking_right = new Animation(walking_right_tex, PLAYER_WIDTH, 0.2);
	animations.climb = new Animation(climb_tex, PLAYER_WIDTH, 0.5);
	animations.steady_climb = new Animation(steady_climb_tex, PLAYER_WIDTH, 0.3);
	animations.back = new Animation(back_tex, PLAYER_WIDTH, 0.5);
	animations.standing_left = new Animation(standing_left_tex, PLAYER_WIDTH, 0.5);
	animations.standing_right = new Animation(standing_right_tex, PLAYER_WIDTH, 0.5);
	animations.jump_left = new Animation(jumping_left_tex, PLAYER_WIDTH, 0.5);
	animations.jump_right = new Animation(jumping_right_tex, PLAYER_WIDTH, 0.5);
}

void Player::draw(double time) {
	current_animation->draw_frame(screen, x, y, time);
}