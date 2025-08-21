#pragma once
#include <SDL3/SDL.h>
#include "Vector2.h"
#include "Game.h"

class Bird
{	
	float gravity = -10;
	bool flapped = false;
	float flapPower = 4;
	float maxVelocity = 6;

public:
	Game* game;
	SDL_Window* window;
	Vector2* position = new Vector2(-5, 0);
	float velocity;

	void Tick();
	Bird(Game* game);
};