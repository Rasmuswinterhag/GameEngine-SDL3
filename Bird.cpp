#include "Bird.h"
#include "CoordinateConverter.h"
#include <iostream>

void Bird::Tick()
{
	const bool* keys = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();

	velocity += gravity * game->fdata.deltaTime;
	if (keys[SDL_SCANCODE_SPACE] && !flapped) {
		if (velocity < 0)
		{
			velocity = flapPower;
		}
		else
		{
			velocity += flapPower * 0.75;
		}
		if (velocity > maxVelocity) { velocity = maxVelocity; }
		flapped = true;
	}
	if (!keys[SDL_SCANCODE_SPACE]) { flapped = false; }
	position->y += velocity * game->fdata.deltaTime;

	CoordinateConverter::SetWindowWorldPosition(window, *(position));
}

Bird::Bird(Game* game)
{
	this->game = game;
	window = SDL_CreateWindow("Bird", 100, 100, 0);
}