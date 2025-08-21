#pragma once
#include <SDL3/SDL.h>
#include "Vector2.h"
#include "Game.h"

class Bird
{	
	float gravity = -4;
	bool flapped = false;

public:
	Game* game;
	SDL_Window* window;
	Vector2* position = new Vector2(-5, 0);
	float velocity;

	void Tick();
	Bird(Game* game);
};