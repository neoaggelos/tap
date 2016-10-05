#ifndef _util_h
#define _util_h

#include "main.h"

void SDL_CHECK(bool test, string error_msg = "SDL Error");
int random(int min, int max);

#endif /* _util_h */