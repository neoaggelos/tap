#include "util.h"

#include <ctime>

void SDL_CHECK(bool test, string error_msg)
{
	if (test)
		return;

	error_msg = error_msg + ": " + SDL_GetError();
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error_msg.c_str(), NULL);
	
	SDL_Quit();
	exit(0);
}

int random(int min, int max)
{
	static bool init = false;

	if (!init) {
		srand((unsigned int)time(NULL));
		init = true;
	}

	return min + rand() % (max - min + 1);
}