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
	int minimumPipes = 4;

public:
	Game* game;
	void Tick();
	PipeManager(Game* game);
	void SpawnTimer();
	void TickPipes();
	void Start();
	Pipe* RequestPipe(float height);
	Pipe* CreateNewPipe(float height = 0);
	std::list<Pipe*> pipes;
};