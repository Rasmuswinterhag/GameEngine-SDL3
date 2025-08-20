#include "ScoreManager.h"
#include "CoordinateConverter.h"
#include <iostream>

ScoreManager::ScoreManager(Game* game, Bird* bird, PipeManager* pipeManager)
{
	this->bird = bird;
	this->pipeManager = pipeManager;

	scoreWindow = SDL_CreateWindow("Score: 0", 325, 0, 0);
	CoordinateConverter::SetWindowWorldPosition(scoreWindow, Vector2(-1, 4.25));
}

void ScoreManager::Tick()
{
	for (Pipe p : pipeManager->pipes)
	{
		
		if (bird->position->x > p.middlePos.x
			&& bird->position->x < p.middlePos.x + CoordinateConverter::ToWorldSpace(p.pipeSize.x))
		{
			AddScore(1);
			p.hasScored = true;
		}
	}
}

void ScoreManager::AddScore(int value)
{
	score += value;
	SDL_SetWindowTitle(scoreWindow, "Score: " + score);
}