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
	switch (game->gameState)
	{
	case Game::GameState::Start:
		Start();
		break;
	case Game::GameState::Playing:
		SpawnTimer();
		TickPipes();
		break;
	case Game::GameState::Dead:
		break;
	}
}

void PipeManager::Start()
{
	if (pipes.size() < minimumPipes)
	{
		CreateNewPipe()->DeactivateWindow();
	}
	for (Pipe* currentPipe : pipes) //TODO: optimise to have a function that only runs once
	{
		currentPipe->DeactivateWindow();
	}
}

void PipeManager::SpawnTimer()
{
	timer += game->fdata.deltaTime;
	if (timer > spawnRate)
	{
		float randomHeight = SDL_rand(7) + minHeight;
		RequestPipe(randomHeight);
		timer = 0;
	}
}

void PipeManager::TickPipes()
{
	for (Pipe* currentPipe : pipes)
	{
		if (currentPipe->middlePos.x > -9)
		{
			currentPipe->Tick();
		}
		else
		{
			//TODO: not deactivation that fucks everything up
			currentPipe->DeactivateWindow();
		}
	}
}

Pipe* PipeManager::RequestPipe(float height)
{
	for (Pipe* currentPipe : pipes)
	{
		if (!currentPipe->active)
		{
			currentPipe->ActivateWindow();
			currentPipe->ResetPipe(height);
			return currentPipe;
		}
	}
	return CreateNewPipe(height);
	//return NULL;
}

Pipe* PipeManager::CreateNewPipe(float height)
{
	std::cout << "Creating window" << '\n';
	Pipe* newPipe = new Pipe(game, height);
	newPipe->ActivateWindow();
	newPipe->ResetPipe(height);
	pipes.emplace_back(newPipe);
	return newPipe;
}
