#include "ScoreManager.h"
#include "CoordinateConverter.h"
#include <string>
#include <iostream>
#include <format>

ScoreManager::ScoreManager(Game* game, Bird* bird, PipeManager* pipeManager)
{
	this->bird = bird;
	this->pipeManager = pipeManager;

	scoreWindow = SDL_CreateWindow("Score: 0", 400, 0, 0);
	CoordinateConverter::SetWindowWorldPosition(scoreWindow, CoordinateConverter::ToWorldSpace(Vector2Int(CoordinateConverter::screenWidth * 0.425, 50)));
}

void ScoreManager::Tick()
{
	for (Pipe* p : pipeManager->pipes)
	{
		if (!p->hasScored &&
			bird->position->x >= p->middlePos.x &&
			bird->position->x <= p->middlePos.x + CoordinateConverter::SizeToWorld(p->pipeSize.x)&&
			bird->position->y >= p->middlePos.y - p->holeDistance &&
			bird->position->y <= p->middlePos.y + p->holeDistance)
		{
			AddScore(1);
			std::cout << "Point! now: " << score << '\n';
			p->hasScored = true;
		}
	}
}

void ScoreManager::AddScore(int value)
{
	score += value;
	SDL_SetWindowTitle(scoreWindow, std::format("Score: {}", score).c_str());
}