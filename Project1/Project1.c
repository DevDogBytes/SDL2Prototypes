#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"

typedef struct
{
	int x, y, width, height;
	short life;
	char* name;
} Man;

typedef struct
{
	Man man;
	SDL_Texture* texture;
} GameState;

int doEvents(SDL_Renderer* renderer, GameState* gameState)
{
	int done = 0;
	const Uint8* state;
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
			done = 1;
			break;
		case SDL_QUIT:
			done = 1;
			break;
		}
	}

	state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT])
	{
		gameState->man.x -= 5;
	}
	if (state[SDL_SCANCODE_UP])
	{
		gameState->man.y -= 5;
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		gameState->man.x += 5;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		gameState->man.y += 5;
	}
	return done;
}

int doRender(SDL_Renderer* renderer, GameState* gameState)
{
	SDL_SetRenderDrawColor(renderer, 0xab, 0xf0, 0xe9, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0x63, 0xb7, 0xaf, 255);
	SDL_Rect rect = { gameState->man.x, gameState->man.y, gameState->man.width, gameState->man.height};
	SDL_RenderCopy(renderer, gameState->texture, NULL, &rect);
	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	int done = 0;

	SDL_Init(SDL_INIT_VIDEO);

	

	window = SDL_CreateWindow("Project1",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	surface = IMG_Load("toad.gif");

	GameState gameState;
	gameState.man.x = 100;
	gameState.man.y = 100;
	gameState.man.width = 96;
	gameState.man.height = 132;
	gameState.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	
	while (!done)
	{
		done = doEvents(renderer, &gameState);
		doRender(renderer, &gameState);
	}

	SDL_DestroyTexture(gameState.texture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}