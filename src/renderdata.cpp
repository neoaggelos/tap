#include "renderdata.h"

static int winx = SDL_WINDOWPOS_CENTERED;
static int winy = SDL_WINDOWPOS_CENTERED;
static int WIDTH = 640;
static int HEIGHT = 480;

RenderData::RenderData()
{
	int r = SDL_Init(SDL_INIT_VIDEO);
	SDL_CHECK(r != -1, "Could not initialize SDL2");

	mWindow = SDL_CreateWindow("Tap", winx, winy, WIDTH, HEIGHT, 0);
	SDL_CHECK(mWindow != NULL, "Could not create window");

	mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
	SDL_CHECK(mRenderer != NULL, "Could not create renderer");

	SDL_Surface* mSurface = SDL_LoadBMP("circle.bmp");
	SDL_CHECK(mSurface != NULL, "Could not load circle.bmp");

	SDL_SetColorKey(mSurface, 1, SDL_MapRGB(mSurface->format, 0xff, 0, 0xff));
	
	mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
	SDL_FreeSurface(mSurface);
	SDL_CHECK(mTexture != NULL, "Could not create texture");

	mFont = SDLU_LoadFont(NULL, 20, 1);
	SDL_CHECK(mFont != NULL, "Could not load default font");
}

RenderData::~RenderData()
{
	SDL_DestroyTexture(mTexture);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDLU_CloseFont(mFont);

	SDL_Quit();
}