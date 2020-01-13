/*
Name: Rhys O'Reilly
Course: GAME202 Object-Oriented Programming
Prof: Majid Moghadam
Title of Program: Game Programming
Date: January 13th, 2020
*/


//
#include "SDL.h"

//
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//
SDL_Renderer *renderer;

//
bool running = true;

//
SDL_Rect PlayerPaddle;
SDL_Rect AIPaddle;
SDL_Rect Ball;

/*
Purpose of the LoadGame function: 
*/
void LoadGame()
{
	//
	SDL_Window *window;

	//
	window = SDL_CreateWindow("Basic SDL Sprites",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (!window) {
		return;
	}

	//
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		return;
	}

	//
	PlayerPaddle.x = 20;
	PlayerPaddle.y = 250;
	PlayerPaddle.h = 100;
	PlayerPaddle.w = 20;

	//
	AIPaddle.x = 760;
	AIPaddle.y = 250;
	AIPaddle.h = 100;
	AIPaddle.w = 20;

	//
	Ball.x = 370;
	Ball.y = 290;
	Ball.h = 20;
	Ball.w = 20;
}

/*
Purpose of the Input function:
*/
void Input() {

}

/*
Purpose of the Update function:
*/
void Update()
{

}

/*
Purpose of the DrawScreen function:
*/
void DrawScreen()
{
	//
	SDL_RenderClear(renderer);

	//
	SDL_Rect background = { 0, 0, 800, 600 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &background);

	//
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &PlayerPaddle);
	SDL_RenderFillRect(renderer, &AIPaddle);

	//
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &Ball);


	//
	SDL_RenderPresent(renderer);
}

/*
Purpose of the Quit function:
*/
void Quit()
{
	//
	SDL_Quit();
}

/*
Purpose of the Main function: 
*/
int main(int argc, char *argv[])
{
	//
	LoadGame();

	//
	while (running == true)
	{
		Input();		//
		Update();		//
		DrawScreen();	//
	}

	//
	Quit();

	return 0;
}