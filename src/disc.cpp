#include "disc.h"

Disc::Disc(int disctype, int radius, int _x, int _y, double _xVel, double _yVel)
{
	xVel = _xVel;
	yVel = _yVel;
	if (xVel == -1 && yVel == -1) {
		xVel = (1 - 2 * random(0,1)) * random(50, 200) / 100.0;
		yVel = (1 - 2 * random(0,1)) * random(50, 200) / 100.0;
	}

	x = _x;
	y = _y;
	if (x == -1 && y == -1) {
		x = random(20, 640 - 100);
		y = random(20, 480 - 100);
	}

	type = disctype;
	rad = radius;
}

void
Disc::move(double var)
{
	x += xVel * var;
	y += yVel * var;

	/* bounce on x */
	if (x >= 640 - 2*rad) {
		x = 640 - 2*rad;
		xVel = -xVel;
	}
	else if (x <= 0) {
		x = 0;
		xVel = -xVel;
	}

	/* bound on y */
	if (y >= 480 - 2*rad) {
		y = 480 - 2*rad;
		yVel = -yVel;
	}
	else if (y <= 0) {
		y = 0;
		yVel = -yVel;
	}
}

void
Disc::render()
{
	SDL_Rect dest = { x, y, 2 * rad, 2 * rad };
	SDL_Color mod;

	switch (type) {
	case 0: mod = { 0xaa, 0xaa, 0xaa, 0xff }; break;
	case 1: mod = { 0xff, 0xff, 0xff, 0xff }; break;
	case 2: mod = { 0xff, 0xff, 0x00, 0xff }; break;
	case 3: /* mod = { 0xff, 0xaa, 0x00, 0xff }; break;
	case 4: */mod = { 0xff, 0x00, 0x00, 0xff }; break;
	default: return;
	}



	SDL_RenderCopy(gSuper->renderData()->renderer(), gSuper->renderData()->texture(mod), NULL, &dest);
}

bool
Disc::contains(Disc * other)
{
	SDL_assert(other);

	if (other->radius() > radius())
		return false;

	float x1 = other->x + other->radius();
	float x2 = x + radius();
	float y1 = other->y + other->radius();
	float y2 = y + radius();

	int dist = SDL_sqrtf((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));

	/* also allow a small 5 pixel margin error */
	return dist - 5 < radius() - other->radius();
}