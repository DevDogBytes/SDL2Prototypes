#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "SDL.h"
#include "SDL_image.h"

typedef struct
{
	int x, y, w, h;
	int sx, sy;
	SDL_Surface* surface;
	SDL_Texture* texture;
} Player;

typedef struct
{
	SDL_Surface* surface;
	SDL_Texture* texture;
} Background;

typedef struct
{
	SDL_Renderer* renderer;
	Player player;
	Background background;
} GameState;

void loadGame(GameState* gameState)
{
	SDL_Renderer* renderer = &gameState->renderer;
	Player* player = &gameState->player;
	Background* background = &gameState->background;

	player->x = 50;
	player->y = 50;
	player->w = 100;
	player->h = 100;
	player->sx = 0;
	player->sy = 0;

	player->surface = IMG_Load("player_2048x8192.png");
	background->surface = IMG_Load("Sidewalk1_middle.png");

	if (player->surface == NULL)
	{
		printf("Cannot load image");
		SDL_Quit();
		exit(1);
	}

	if (background->surface == NULL)
	{
		printf("Cannot load image");
		SDL_Quit();
		exit(1);
	}

};

int processEvents(GameState* gameState)
{
	SDL_Renderer* renderer = gameState->renderer;

	Player* player = &gameState->player;

	SDL_Event event;
	int stop = 0;

	SDL_PollEvent(&event);

	const Uint8* state = SDL_GetKeyboardState(NULL);	

	if (state[SDL_SCANCODE_LEFT])
	{
		player->x -= 10;
		player->sx = 1024;
		player->sy = 4608;
	}
	if (state[SDL_SCANCODE_UP])
	{
		player->y -= 10;
		player->sx = 0;
		player->sy = 2048;
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		player->x += 10;
		player->sx = 1024;
		player->sy = 6656;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		player->y += 10;
		player->sx = 0;
		player->sy = 0;
	}
	if (!(state[SDL_SCANCODE_LEFT] | state[SDL_SCANCODE_UP] | state[SDL_SCANCODE_RIGHT] | state[SDL_SCANCODE_DOWN]))
	{
		if (player->sy == 6656 || player->sy == 4608)
		{
			player->sx = 0;
			player->sy = 0;
		}
	}

	return stop;
};

void doRender(GameState* gameState)
{
	SDL_Renderer* renderer = gameState->renderer;
	Player* player = &gameState->player;
	
	SDL_SetRenderDrawColor(renderer, 0xff, 0xc4, 0xa3, 0xff);
	SDL_RenderClear(renderer);
	SDL_Rect rectSrc = { player->sx, player->sy, 512, 512 };
	SDL_Rect rectDst = { player->x, player->y, player->w, player->h };

	
	SDL_RenderCopy(renderer, player->texture, &rectSrc, &rectDst);


	SDL_RenderPresent(renderer);
};

int main(int argc, char* argv[])
{
	int stop = 0;
	SDL_Window* window = NULL;
	GameState gameState;
	gameState.player.texture = NULL;
	gameState.player.surface = NULL;
	Player* player = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);	

	window = SDL_CreateWindow("Project1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	gameState.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	renderer = gameState.renderer;

	loadGame(&gameState);
	gameState.player.texture = SDL_CreateTextureFromSurface(renderer, gameState.player.surface);
	gameState.background.texture = SDL_CreateTextureFromSurface(renderer, gameState.background.surface);

	while (!stop)
	{
		processEvents(&gameState);
		doRender(&gameState);		
	}


	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(gameState.renderer);
	SDL_DestroyTexture(gameState.player.texture);
	SDL_Quit(SDL_QUIT);
}