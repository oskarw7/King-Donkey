#include "Player.h"

//sprawdza, czy gracz jest na drabinie
int Player::on_ladder(Map* map) {
	for (int i = 0; i < map->ladders.get_size(); i++) {
		if (isTierceCollision(map->ladders.get(i))) {
			return 1;
		}
	}
	for (int i = 0; i < map->upper_ladders.get_size(); i++) {
		if (isTierceCollision(map->upper_ladders.get(i))) {
			return 1;
		}
	}
	return 0;
	
}

//sprawdza, czy gracz jest na ziemi
int Player::on_ground(Map* map) {
	for (int i = 0; i < map->tiles.get_size(); i++) {
		if (isOn(map->tiles.get(i))) { 
			return 1;
		}
	}
	return 0;

}

//sprawdza, czy gracz jest nad drabina
int Player::above_ladder(Map* map) {
	for (int i = 0; i < map->upper_ladders.get_size(); i++) {
		if (isTierceOn(map->upper_ladders.get(i))) {
			return 1;
		}
	}
	return 0;

}

//przesuwa gracza, sprawdza skrajne przypadki (wyjscie poza ekran)
void Player::player_move(double mx, double my) {
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

//odpowiada za przyspieszenie grawitacyjne gracza oraz zerowanie flag i predkosci w przypadku kolizji z podlozem
void Player::players_gravity(double time, Map* map) {
	if (on_ladder(map) || on_ground(map)) {
		isJumping = 0;
		velocity_x = PLAYER_VELOCITY_X;
		velocity_y = JUMP_VELOCITY;
		return;
	}
	velocity_y += GRAVITY * time;
	player_move(0, velocity_y * time + GRAVITY * time * time);
}

void Player::load_player_graphics() {
	run_left_tex = SDL_LoadBMP(RUN_LEFT_PATH);
	if (run_left_tex == NULL)
		load_error(RUN_LEFT_PATH);

	run_right_tex = SDL_LoadBMP(RUN_RIGHT_PATH);
	if (run_right_tex == NULL)
		load_error(RUN_RIGHT_PATH);

	climb_tex = SDL_LoadBMP(CLIMB_PATH);
	if (climb_tex == NULL)
		load_error(CLIMB_PATH);

	steady_climb_tex = SDL_LoadBMP(STEADY_CLIMB_PATH);
	if (steady_climb_tex == NULL) 
		load_error(CLIMB_PATH);

	back_tex = SDL_LoadBMP(BACK_PATH);
	if (back_tex == NULL) 
		load_error(CLIMB_PATH);


	stand_left_tex = SDL_LoadBMP(STAND_LEFT_PATH);
	if (stand_left_tex == NULL) 
		load_error(STAND_LEFT_PATH);

	stand_right_tex = SDL_LoadBMP(STAND_RIGHT_PATH);
	if (stand_right_tex == NULL) 
		load_error(STAND_RIGHT_PATH);

	jump_left_tex = SDL_LoadBMP(JUMP_LEFT_PATH);
	if (jump_left_tex == NULL) 
		load_error(JUMP_LEFT_PATH);

	jump_right_tex = SDL_LoadBMP(JUMP_RIGHT_PATH);
	if (jump_right_tex == NULL) 
		load_error(JUMP_RIGHT_PATH);

	animations.run_left = new Animation(run_left_tex, PLAYER_WIDTH, 0.2);
	animations.run_right = new Animation(run_right_tex, PLAYER_WIDTH, 0.2);
	animations.climb = new Animation(climb_tex, PLAYER_WIDTH, 0.5);
	animations.steady_climb = new Animation(steady_climb_tex, PLAYER_WIDTH, 0.3);
	animations.back = new Animation(back_tex, PLAYER_WIDTH, 0.5);
	animations.stand_left = new Animation(stand_left_tex, PLAYER_WIDTH, 0.5);
	animations.stand_right = new Animation(stand_right_tex, PLAYER_WIDTH, 0.5);
	animations.jump_left = new Animation(jump_left_tex, PLAYER_WIDTH, 0.5);
	animations.jump_right = new Animation(jump_right_tex, PLAYER_WIDTH, 0.5);
}

void Player::draw(double time, Map* map) {
	current_animation->draw_frame(screen, (int)x, (int)y, time);
}


Player::~Player() {
	delete current_animation;
	SDL_FreeSurface(run_left_tex);
	SDL_FreeSurface(run_right_tex);
	SDL_FreeSurface(climb_tex);
	SDL_FreeSurface(steady_climb_tex);
	SDL_FreeSurface(back_tex);
	SDL_FreeSurface(stand_left_tex);
	SDL_FreeSurface(stand_right_tex);
	SDL_FreeSurface(jump_left_tex);
	SDL_FreeSurface(jump_right_tex);
}