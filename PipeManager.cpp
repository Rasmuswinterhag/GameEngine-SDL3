#include "PipeManager.h"
#include <iostream>

PipeManager::PipeManager(Game* game)
{
	this->game = game;
	spawnRate = 1
		;
	timer = spawnRate; //To spawn a pipe immediately
}

void PipeManager::Tick()
{
	timer += game->fdata.deltaTime;
	if (timer > spawnRate)
	{
		float randomHeight = SDL_rand(7) + minHeight;
		RequestPipe(randomHeight);
		timer = 0;
	}


	for (auto it = pipes.begin(); it != pipes.end(); )
	{
		if (it->middlePos.x > -9)
		{
			it->Tick();
			++it;
		}
		else
		{
			//TODO: not deactivation that fucks everything up
    		it->DeactivateWindow();
		}
	}
}

Pipe PipeManager::RequestPipe(float height)
{
	for (Pipe currentPipe : pipes)
	{
 		if (!currentPipe.active)
		{
			std::cout << "reuse" << '\n';
			currentPipe.middlePos = Vector2(-9, height);
			currentPipe.ActivateWindow();
			return currentPipe;
		}
	}
	std::cout << "spawn new" << '\n';
	Pipe newPipe = Pipe(game, height);
	newPipe.ActivateWindow();
	pipes.emplace_back(newPipe);
	return newPipe;
	//return NULL;
}
