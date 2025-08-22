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
	position->y = 0; //TODO: optimise to have a function that only runs once
	velocity = 0; //TODO: optimise to have a function that only runs once
	const bool* keys = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();
	if (keys[SDL_SCANCODE_SPACE])
	{
		game->SetGameState(Game::GameState::Playing);
		std::cout << "Play" << '\n';
	}

	CoordinateConverter::SetWindowWorldPosition(window, *(position)); //TODO: Move the position to be in the center of the window
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

	if (position->y > CoordinateConverter::worldHeight/2) //Ceiling handling
	{
 		velocity = 0;
		position->y = CoordinateConverter::worldHeight / 2;
	}
	else if (position->y < -CoordinateConverter::worldHeight / 2) //Floor handling
	{
		game->SetGameState(Game::GameState::Dead);
	}

	position->y += velocity * game->fdata.deltaTime;
	CoordinateConverter::SetWindowWorldPosition(window, *(position));
}

void Bird::Dead()
{
	const bool* keys = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();
	if (keys[SDL_SCANCODE_SPACE])
	{
		game->SetGameState(Game::GameState::Start);
		std::cout << "Restart" << '\n';
	}
}

Bird::Bird(Game* game)
{
	this->game = game;
	window = SDL_CreateWindow("Bird", 100, 100, 0);
}