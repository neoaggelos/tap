#include "game.h"

#define TIMEOUT 5000

Game::Game()
{
	player = new Disc(6, 30, 3000, 3000, 0,0);
	running = NULL;
	score = 0;
}

Game::~Game()
{
	delete player;
	if (running) delete running;
}

void
Game::add_disc()
{
	if (running) delete running;

	running = new Disc(random(1, 3), 15);
	end_time = SDL_GetTicks() + TIMEOUT;
}

void
Game::run()
{
	SDL_bool done = SDL_FALSE;
	SDL_Event event;
	SDL_Renderer *renderer = gSuper->renderData()->renderer();
	add_disc();
	SDLU_FPS_Init(60);
	while (SDL_GetTicks() < end_time) {
		SDLU_FPS_Start();
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gSuper->finish();
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT && (SDL_GetTicks() - click_time) > 300) {
					player->x = event.button.x - player->radius();
					player->y = event.button.y - player->radius();
					click_time = SDL_GetTicks();
				}
			}
		}
		if (running && player->type == running->type && player->contains(running)) {
			add_disc();
			score += 10;
		}
		else if (running) {
			running->move(1);
		}

		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0xff);
		SDL_RenderClear(renderer);

		if (click_time) {
			player->type = (SDL_GetTicks() - click_time) / 400;
			if (player->type < 5) {
				player->render();
			}
			else {
				click_time = 0;
			}
		}
		if (running) running->render();

		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		char msg[100];
		SDL_snprintf(msg, 99, "%.1lfs", (end_time - SDL_GetTicks()) / 1000.0);
		SDLU_RenderUTF8(renderer, gSuper->renderData()->font(), msg, 0, 0);
		SDL_snprintf(msg, 99, "%d", score);

		SDLU_RenderUTF8(renderer, gSuper->renderData()->font(), msg, 100, 0);

		SDL_RenderPresent(renderer);
		SDLU_FPS_Cap();
	}

	SDL_Surface * screenshot = SDL_CreateRGBSurface(0, 640, 480, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ABGR8888, screenshot->pixels, screenshot->pitch);
	
	char msg[100];
	SDL_snprintf(msg, 99, "Your score: %d", score);
	SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, screenshot);
	SDL_SetTextureColorMod(background, 150, 150, 150);
	SDL_FreeSurface(screenshot);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, background, NULL, NULL);
	SDL_Rect msgRect = { 120, 120, 420, 240 };

	SDL_SetRenderDrawColor(renderer, 0xff, 0, 0, 0xff);
	SDL_RenderDrawRect(renderer, &msgRect);
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0x8a);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &msgRect);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDLU_RenderUTF8Ex(renderer, gSuper->renderData()->font(), msg, msgRect, Center, Center);

	SDL_RenderPresent(renderer);

	SDL_PumpEvents();
	SDL_FlushEvents(0, (Uint32)-1);

	bool playagain = false;
	while (event.type != SDL_QUIT) {
		SDL_PollEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			playagain = true;
			score = 0;
			break;
		}
		SDL_Delay(1);
	}

	SDL_DestroyTexture(background);

	if (playagain)
		run();
}