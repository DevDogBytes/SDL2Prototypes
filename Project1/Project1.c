#include <stdio.h>
#include "SDL.h"

int processEvents(SDL_Window* window)
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
			}
			break;
		case SDL_QUIT:
			done = 1;
			break;
		}
	}

	return done;
}

void doRender(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 127, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 127, 127, 255);
	SDL_Rect rect = { 100, 100, 200, 200 };
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

	window = SDL_CreateWindow("Project1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	while (!done)
	{
		done = processEvents(&window);
		doRender(&renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}