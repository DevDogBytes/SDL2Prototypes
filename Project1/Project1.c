#include <stdio.h>
#include "SDL.h"

typedef struct
{
	int x, y;
} Man;

void doEvents(SDL_Renderer* renderer, Man* man)
{
	SDL_Event event;
	int done = 0;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
			done = 1;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				man->x -= 10;
				break;
			case SDLK_UP:
				man->y -= 10;
				break;
			case SDLK_RIGHT:
				man->x += 10;
				break;
			case SDLK_DOWN:
				man->y += 10;
				break;
			}
			break;
		case SDL_QUIT:
			done = 1;
			break;
		}
	}
}

void doRender(SDL_Renderer* renderer, Man* man)
{
	SDL_SetRenderDrawColor(renderer, 0xfe, 0xe2, 0xb3, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0xff, 0xa2, 0x99, 255);
	SDL_Rect rect = { man->x, man->y, 100, 100 };
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);
}

void doCollisions()
{

}

int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	Man man;
	int done = 0;

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Project1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	man.x = 100;
	man.y = 100;	

	while (!done)
	{
		doEvents(renderer, &man);
		doRender(renderer, &man);
	}	
}