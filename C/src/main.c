#include "header.h"

void	setup() {
	g_game.playerX = 0;
	g_game.playerY = 0;
}

void	processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT: {
			g_game.isRunning = FALSE;
			break;
		}
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				g_game.isRunning = FALSE;
			break;
		}
	}
}

void	update() {
	//act like a FPS counter
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), g_game.ticksLastFrame + FRAME_TIME_LENGTH));

	float	deltaTime = (SDL_GetTicks() - g_game.ticksLastFrame) / 1000.0f;
	printf("FPS = %f\n", deltaTime);
	
	g_game.ticksLastFrame = SDL_GetTicks();
	g_game.playerX += 50 * deltaTime;
	g_game.playerY += 50 * deltaTime;
}

void	render() {
	SDL_SetRenderDrawColor(g_renderer, 155, 155, 0, 255);
	SDL_RenderClear(g_renderer);

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_Rect rect = {g_game.playerX, g_game.playerY, 20, 20};
	SDL_RenderFillRect(g_renderer, &rect);

	SDL_RenderPresent(g_renderer);
}


int	main() {
	initGlobal();
	g_game.isRunning = initWindow();

	setup();

	while (g_game.isRunning) {
		processInput();
		update();
		render();
	}

	destroyWindow();
	return 0;
}