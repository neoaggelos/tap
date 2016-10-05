#ifndef _super_h
#define _super_h

#include "main.h"

class Super {
private:
	RenderData *mRenderData;
	Game *mGame;

public:
	Super();
	~Super();

	RenderData *renderData() { return mRenderData; };
	Game *game() { return mGame; };

	void playGame();
	void finish();
};

#endif /* _super_h */