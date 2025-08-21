#include "Bird.h"
#include "CoordinateConverter.h"
#include <iostream>

void Bird::Tick()
{
	switch (game->gameState)
	{
	case Game::GameState::Start:
		Start();
		break;
	case Game::GameState::Playing:
		Playing();
		break;
	case Game::GameState::Dead:
		Dead();
		break;
	}
}

void Bird::Start()
{
	const bool* keys = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();
	if (keys[SDL_SCANCODE_SPACE])
	{
		game->SetGameState(Game::GameState::Playing);
	}

	CoordinateConverter::SetWindowWorldPosition(window, *(position));
}

void Bird::Playing()
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

void Bird::Dead()
{

}

Bird::Bird(Game* game)
{
	this->game = game;
	window = SDL_CreateWindow("Bird", 100, 100, 0);
}