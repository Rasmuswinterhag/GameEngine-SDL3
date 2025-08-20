#include "Bird.h"
#include "CoordinateConverter.h"
#include <iostream>

void Bird::Tick()
{
	const bool* keys = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();

	velocity += gravity * game->fdata.deltaTime;
	if (keys[SDL_SCANCODE_SPACE] && !flapped) { velocity = 5; flapped = true; }
	if (!keys[SDL_SCANCODE_SPACE]) { flapped = false; }
	position->y += velocity * game->fdata.deltaTime;

	CoordinateConverter::SetWindowWorldPosition(window, *(position));
	std::cout << position->x << "\n";
}

Bird::Bird(Game* game)
{
	this->game = game;
	window = SDL_CreateWindow("Bird", 100, 100, 0);
}