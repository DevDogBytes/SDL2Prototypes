#include <stdio.h>
#include "SDL.h"

typedef struct
{
	int x, y;
	short life;
	char* name;
} Man;

int processEvents(SDL_Window* window, Man* man)
{
	SDL_Event event;
	int done = 0;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
			if (window)
			{
				SDL_DestroyWindow(window);
				window = NULL;
				done = 1;
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				done = 1;
				break;
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

	return done;
}

void doRender(SDL_Renderer* renderer, Man* man)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 127, 127, 255);
	SDL_Rect rect = { man->x, man->y, 200, 200 };
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);
}


int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	int done = 0;
	Man man;

	window = SDL_CreateWindow("Project1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	man.x = 100;
	man.y = 100;
	man.name = "Man";
	man.life = 10;

	while (!done)
	{
		done = processEvents(window, &man);
		doRender(renderer, &man);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}