#pragma once
#include <SDL3/SDL.h>
#include "Bird.h"
#include "Game.h"

class HitManager
{
	Bird* bird;
	PipeManager* pipeManager;
	Game* game;

public:
	SDL_Window* scoreWindow;
	int score = 0;
	void AddScore(int value);
	void SetScore(int value);
	HitManager(Game* game, Bird* bird, PipeManager* pipeManager);
	void Tick();
	void Start();
	void Playing();
	void Dead();
};