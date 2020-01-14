/*
Name: Rhys O'Reilly
Course: GAME202 Object-Oriented Programming
Prof: Majid Moghadam
Title of Program: Game Programming
Date: January 13th, 2020
*/


//
#include "SDL.h"
#include <cstdlib>

//
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//
SDL_Renderer *renderer;

//
SDL_Event event;

// Mouse coordinates
int mouse_x, mouse_y;

int speed_x, speed_y;
int direction[2] = { -1, 1 };

//
bool running = true;

//
SDL_Rect PlayerPaddle;
SDL_Rect AIPaddle;
SDL_Rect Ball;
SDL_Rect MiddleLine;

bool check_collision(SDL_Rect A, SDL_Rect B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}
	
	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside of B
	return true;
}

/*
Purpose of the LoadGame function: is to load up the game initially
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

	//
	MiddleLine.x = 400;
	MiddleLine.y = 0;
	MiddleLine.h = 600;
	MiddleLine.w = 10;

}

/*
Purpose of the Input function: is to detect user input
*/
void Input() {
	//queing events
	while (SDL_PollEvent(&event)) {

		//track mouse movement
		if (event.type == SDL_MOUSEMOTION)
			SDL_GetMouseState(&mouse_x, &mouse_y);

		//clicking 'x' or pressing f4
		if (event.type == SDL_QUIT)
			running = false;

		//pressing a key
		if (event.type == SDL_KEYDOWN)
			switch (event.key.keysym.sym)
			{
				//pressing ESC exits from the game
			case SDLK_ESCAPE:
				running = false;
				break;
			}
	}
}

/*
Purpose of the Update function: is to change the game to react to the user input
*/
void Update()
{
	PlayerPaddle.y = mouse_y;

	if (Ball.x < 0 || Ball.x > WINDOW_WIDTH)
	{
		Ball.x = WINDOW_WIDTH / 2;
		Ball.y = WINDOW_HEIGHT / 2;
		//this expression produces the random numbers -1, -2, 1 and 2
		speed_x = (rand() % 2 + 1) * direction[rand() % 2];
		speed_y = (rand() % 2 + 1) * direction[rand() % 2];
	}

	Ball.x += speed_x;
	Ball.y += speed_y;

	SDL_Delay(5);

	if (Ball.y < 0 || Ball.y >(WINDOW_HEIGHT - Ball.h))
	{
		speed_y = -speed_y;
	}

	AIPaddle.y = Ball.y - AIPaddle.h / 2 + Ball.h / 2;

	if (check_collision(Ball, AIPaddle) || check_collision(Ball, PlayerPaddle))
	{
		speed_x = -speed_x;
	}
}

/*
Purpose of the DrawScreen function: is to render the game world after the changes from user input have been made
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
	SDL_RenderFillRect(renderer, &MiddleLine);

	//
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &Ball);


	//
	SDL_RenderPresent(renderer);
}

/*
Purpose of the Quit function: to exit the application
*/
void Quit()
{
	//
	SDL_Quit();
}

/*
Purpose of the Main function: the main game loop. required for anything to happen. lasts as long as it doesnt crash and user doesnt exit.
*/
int main(int argc, char *argv[])
{
	//
	LoadGame();
	{
		speed_x = -1;
		speed_y = -1;
	}

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