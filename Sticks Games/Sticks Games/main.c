#include "Sticks.h"

int main(void) {

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_bool isRunning = SDL_TRUE;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_HandleError("SDL Init failed");

	window = SDL_CreateWindow("Sticks game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (window == NULL)
		SDL_HandleError("Failed to create window");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		SDL_HandleError("Failed to create renderer");

	initPlayer();
	initBoard();

	while (isRunning) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = SDL_FALSE;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					isRunning = SDL_FALSE;
				break;
			default:
				break;
			}
		}
		createStick(renderer, stickNb);
		stickControl(&event);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}