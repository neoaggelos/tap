#include "super.h"

Super::Super()
{
	mRenderData = new RenderData;
	mGame = NULL;
}

Super::~Super()
{
	finish();
}

void
Super::playGame()
{
	mGame = new Game;

	mGame->run();

	delete mGame;
}

void
Super::finish()
{
	if (mGame) delete mGame;

	delete mRenderData;
	exit(0);
}