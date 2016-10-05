#ifndef _renderdata_h
#define _renderdata_h

#include "main.h"

class RenderData {
private:
	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;
	SDL_Texture *mTexture;
	SDLU_Font * mFont;

public:
	RenderData();
	~RenderData();

	SDL_Window *window() { return mWindow; }
	SDL_Renderer *renderer() { return mRenderer; }
	SDL_Texture *texture(SDL_Color fill) { SDL_SetTextureColorMod(mTexture, fill.r, fill.g, fill.b); return mTexture; }
	SDLU_Font* font() { return mFont; }
};

#endif /* _renderdata_h */