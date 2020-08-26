#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL.h>

#define WIDTH 900
#define HEIGHT 900
#define SCL 3
#define ROWS WIDTH / SCL
#define COLS HEIGHT / SCL

typedef struct Cell {
	int x;
	int y;
	int cellState;
}Cell;

SDL_Rect rectangle;
Cell* cell[COLS]; int* oldGen[COLS];
int genCount = 0;

void SDLErrorCheck(const char* errorMsg){
	SDL_Log("%s -> %s\n", errorMsg, SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

void createCell(SDL_Renderer* renderer, int x, int y, int cellState) {
	rectangle.x = x; rectangle.y = y;
	rectangle.w = SCL; rectangle.h = SCL;

	if (cellState == 0) { //Cell state dead --> white
		if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0)
			SDLErrorCheck("Failed to change render color");
	}
	else if (cellState == 1) { //Cell state alive --> black
		if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
			SDLErrorCheck("Failed to change render color");
	}

	if (SDL_RenderFillRect(renderer, &rectangle) != 0) //Draw cell
		SDLErrorCheck("Failed to draw rectangle");
}

int neighborsNumber(int i, int j) {
	int count = 0;

	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			if (oldGen[i + x][j + y] == 1) {
				if (x == 0 && y == 0)
					continue;
				else
					count++;
			}
		}
	}

	return count;
}

void initNewGen() {
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (oldGen[i][j] == 1) { //Cell is alive
				if (neighborsNumber(i, j) < 2)
					cell[i][j].cellState = 0;
				if (neighborsNumber(i, j) > 3)
					cell[i][j].cellState = 0;
				if (neighborsNumber(i, j) == 2 || neighborsNumber(i, j) == 3)
					cell[i][j].cellState = 1;
			}
			else if (oldGen[i][j] == 0) { //Cell is dead
				if (neighborsNumber(i, j) == 3)
					cell[i][j].cellState = 1;
			}
		}
	}
}

void displayGen(SDL_Renderer* renderer) {
	
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS; j++) {

			//Config current generation
			cell[i][j].x = (SCL * j);
			cell[i][j].y = (SCL * i);

			//Draw generation
			createCell(renderer, cell[i][j].x, cell[i][j].y, cell[i][j].cellState);

			//Backup current generation
			oldGen[i][j] = cell[i][j].cellState;
		}
	}
}

void init2DArray() {
	srand(time(NULL));

	//Allocate memory for 2D arrays
	for (int i = 0; i < COLS; i++)
		cell[i] = calloc(sizeof(Cell), ROWS * COLS);

	for (int i = 0; i < COLS; i++)
		oldGen[i] = calloc(sizeof(int), ROWS * COLS);

	//Assign random states to cells 
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (cell[i] == NULL)
				exit(1);
			cell[i][j].cellState = rand() % 2;
		}
	}
}