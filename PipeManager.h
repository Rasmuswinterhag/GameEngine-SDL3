#pragma once
#include <list>
#include "Pipe.h"
#include "Game.h"

class PipeManager
{
	float spawnRate;
	float timer;
	float minHeight = -2;
	float maxHeight = 3;

public:
	Game* game;
	void Tick();
	PipeManager(Game* game);
	Pipe RequestPipe(float height);
	std::list<Pipe> pipes;
};