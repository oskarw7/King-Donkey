#ifndef DONKEY_KONG_H

#define DONKEY_KONG_H

#include "Object.h"
#include "Animation.h"

#define KONG_START_X 17
#define KONG_START_Y 147
#define KONG_WIDTH 81
#define KONG_HEIGHT 59

class DonkeyKong : public Object {
public:
	DonkeyKong(int x, int y, SDL_Surface* texture, SDL_Surface* screen) : Object(x, y, KONG_WIDTH, KONG_HEIGHT, screen) {
		this->texture = texture;
		animation = new Animation(texture, KONG_WIDTH, 1);
		this->hasThrown = 1;
	};
	void draw(double time);
	int get_frame_index();

	int hasThrown;

	~DonkeyKong();
private:
	SDL_Surface* texture;
	Animation* animation;
};

#endif