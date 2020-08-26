#include "GameOfLife.h"

/*

	Note : 
		Cell alive --> black
		Cell dead --> white

	Rules :
		case alive:
			- Cell with neighbors < 2 --> Dies next generation 
			- Cell with neighbors > 3 --> Dies next generation 
			- Cell with neighbors = 2-3 --> Lives next generation

		case dead:
			- Cell with neighbors = 3 --> Comes to life next generation
*/

void itsDebugTime();
void displayGenCount();

int main(void)
{

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_bool isRunning = SDL_TRUE;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		SDLErrorCheck("SDL Init failed");

	window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (window == NULL)
		SDLErrorCheck("Failed to create window");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == NULL)
		SDLErrorCheck("Failed to create renderer");

	init2DArray();

	while (isRunning) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE)
					isRunning = SDL_FALSE;
				isRunning = SDL_FALSE;
			}
		}
		displayGen(renderer);
		displayGenCount();
		initNewGen();
		SDL_RenderPresent(renderer);
	}

	//itsDebugTime();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

void displayGenCount() {
	system("cls");
	printf("%d", genCount);
	genCount++;
}

void itsDebugTime() {
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS; j++) {
			printf("%d", oldGen[i][j]);
		}
		printf("\n");
	}
}