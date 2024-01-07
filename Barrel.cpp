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
	velocity_y += GRAVITY * delta;
	move(0, velocity_y * delta);
	jump_hitbox->move(0, velocity_y * delta);
	//move(0, GRAVITY*delta);
	//jump_hitbox->move(0, GRAVITY*delta);
}

void Barrel::update(Map* map, double delta) {
	if (!on_ground(map) && !change_direction && x>=0) {
		current_animation = animations.falling;
		vector *= -1;
		change_direction = 1;
	}
	else if (on_ground(map) && change_direction) {
		velocity_y = BARREL_VELOCITY_Y;
		current_animation = animations.rolling;
		change_direction = 0;
	}

	if (on_ground(map)) {
		move(vector * BARREL_VELOCITY_X *delta, 0);
		jump_hitbox->move(vector * BARREL_VELOCITY_X  * delta, 0);
	}
}

int Barrel::isOut() {
	if (x >= screen->w || x<=0) {
		return 1;
	}
	return 0;
}

void Barrel::load_barrel_graphics() {
	rolling_tex = SDL_LoadBMP(ROLLING_PATH);
	if (rolling_tex == NULL) {
		//load_error(rolling_tex, ROLLING_PATH);
		exit(1);
	}

	falling_tex = SDL_LoadBMP(FALLING_PATH);
	if (falling_tex == NULL) {
		//load_error(falling_tex, FALLING_PATH);
		exit(1);
	}

	animations.rolling = new Animation(rolling_tex, BARREL_WIDTH, 0.25);
	animations.falling = new Animation(falling_tex, HORIZONTAL_BARREL, 0.25);
}

void Barrel::draw(double time) {
	current_animation->draw_frame(screen, x, y, time);
}

Barrel::~Barrel() {
	delete jump_hitbox;
	delete current_animation;
	SDL_FreeSurface(texture);
}