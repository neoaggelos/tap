#ifndef _game_h
#define _game_h

#include "main.h"

class Game {
private:
	Uint32 end_time;
	Disc *running;
	
	Disc *player;
	Uint32 click_time;

	int score;

	void add_disc();

public:

	Game();
	~Game();

	void run();
};

#endif /* _game_h */