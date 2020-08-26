#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL.h>

#define WIDTH 1000
#define HEIGHT 400

typedef struct Stick {
	int x;
	int y;
	int isOnBoard;
	int stickSelNb;
}Stick;

typedef struct Player {
	int id;
	char* playerName;
}Player;

const int MAX = 30, MIN = 10, borderW = 20, borderH = 10, space = 10, maxCharacter = 26;
int stickNb = 0, mouseX, mouseY, player;

Player player1, player2;
SDL_Rect rectangle;
Stick* stick;

void SDL_HandleError(char* errorMsg) {
	SDL_Log("%s -> %s", errorMsg, SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

void initBoard() {
	srand(time(0));
	stickNb = (rand() % (MAX - MIN + 1) + MIN);
	stick = malloc(sizeof(Stick) * stickNb);
	for (int i = 0; i < stickNb; i++) {
		if (stick == NULL)
			exit(1);
		stick[i].isOnBoard = 1;
		stick->stickSelNb = 0;
	}
}

void initPlayer() {
	player1.id = 0; player2.id = 1;
	srand(time(0));

	player1.playerName = (char*)malloc(maxCharacter);
	player2.playerName = (char*)malloc(maxCharacter);

	fprintf(stdout, "Entrez votre nom joueur 1 : ");
	fgets(player1.playerName, maxCharacter, stdin);

	fprintf(stdout, "Entrez votre nom joueur 2 : ");
	fgets(player2.playerName, maxCharacter, stdin);

	player = rand() % 2;
	if (player == player1.id)
		fprintf(stdout, "C'est a %s de commencer", player1.playerName);
	else
		fprintf(stdout, "C'est a %s de commencer !", player2.playerName);
}

void stickControl(SDL_Event* event) {
	SDL_GetMouseState(&mouseX, &mouseY);
	for (int i = 0; i < stickNb; i++) {
		if ((mouseX > stick[i].x && mouseY > stick[i].y) && (mouseX < stick[i].x + rectangle.w && mouseY < stick[i].y + rectangle.h)) {
			if (event->type == SDL_MOUSEBUTTONDOWN && stick[i].isOnBoard != 0) {
				if (event->button.button == SDL_BUTTON_LEFT && stick->stickSelNb < 3) {
					stick[i].isOnBoard = 2;
					stick->stickSelNb++;
					SDL_Delay(150);
				}
				else if (event->button.button == SDL_BUTTON_RIGHT) {
					stick[i].isOnBoard = 1;
					stick->stickSelNb--;
					SDL_Delay(150);
				}
			}
		}
		if (event->type == SDL_KEYDOWN) {
			if (event->key.keysym.sym == SDLK_RETURN) {
				if (stick[i].isOnBoard == 2) {
					stick[i].isOnBoard = 0;
					stick->stickSelNb = 0;
				}
			}
		}
	}

}

void createStick(SDL_Renderer* renderer, int stickNumber) {
	int fuck = WIDTH - (space * (stickNb - 1) + borderW * 2);

	rectangle.x = borderW;
	rectangle.y = borderH;

	rectangle.w = fuck / stickNb;
	rectangle.h = HEIGHT - (borderH * 2);

	for (int i = 0; i < stickNumber; i++) {
		rectangle.x = ((rectangle.w * i) + (space * i)) + borderW;
		stick[i].x = rectangle.x;
		stick[i].y = rectangle.y;

		if (stick[i].isOnBoard == 1) {
			if (SDL_SetRenderDrawColor(renderer, 193, 154, 107, 255) != 0)
				SDL_HandleError("Failed to change render color");
		}
		else if (stick[i].isOnBoard == 0) {
			if (SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255) != 0)
				SDL_HandleError("Failed to change render color");
		}
		else if (stick[i].isOnBoard == 2) {
			if (SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) != 0)
				SDL_HandleError("Failed to change render color");
		}
		if (SDL_RenderFillRect(renderer, &rectangle) != 0)
			SDL_HandleError("Failed to draw rectangle");
	}
}