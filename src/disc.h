#ifndef _disc_h
#define _disc_h

#include "main.h"

class Disc {
private:
	double xVel, yVel;
	double rad;

public:
	Disc(int type, int rad,int x = -1, int y = -1, double xVel = -1, double yVel = -1 );
	~Disc() { }

	double radius() { return rad; }

	int type; /* 0, 1, 2 */
	double x, y;

	void move(double var);
	void render();

	bool contains(Disc * other);
};

#endif /* _disc_h */