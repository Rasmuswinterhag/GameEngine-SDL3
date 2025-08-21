#include "ScoreManager.h"
#include "CoordinateConverter.h"
#include <string>
#include <iostream>
#include <format>

ScoreManager::ScoreManager(Game* game, Bird* bird, PipeManager* pipeManager)
{
	this->game = game;
	this->bird = bird;
	this->pipeManager = pipeManager;

	scoreWindow = SDL_CreateWindow("Score: 0", 400, 0, 0);
	SDL_SetWindowAlwaysOnTop(scoreWindow, true);
	CoordinateConverter::SetWindowWorldPosition(scoreWindow, CoordinateConverter::ToWorldSpace(Vector2Int(CoordinateConverter::screenWidth * 0.425, 50)));
}

void ScoreManager::Tick()
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

void ScoreManager::Start()
{

}

void ScoreManager::Playing()
{
	for (Pipe* p : pipeManager->pipes)
	{
		if (!p->hasBeenHit && //Score hitbox
			bird->position->x >= p->middlePos.x &&
			bird->position->x <= p->middlePos.x + CoordinateConverter::SizeToWorld(p->pipeSize.x) &&
			bird->position->y >= p->middlePos.y - p->holeDistance &&
			bird->position->y <= p->middlePos.y + p->holeDistance)
		{
			AddScore(1);
			p->hasBeenHit = true;
			std::cout << "scored" << '\n';
		}
		else if (!p->hasBeenHit && //top pipe Hitbox
			bird->position->x >= p->topPipePos->x &&
			bird->position->x <= p->topPipePos->x + CoordinateConverter::SizeToWorld(p->pipeSize.x) &&
			bird->position->y <= p->topPipePos->y &&
			bird->position->y >= p->topPipePos->y - CoordinateConverter::SizeToWorld(p->pipeSize.y))
		{
			std::cout << "hit the top" << '\n';
			p->hasBeenHit = true;
			game->gameState = Game::GameState::Dead;
		}
		else if (!p->hasBeenHit && //bottom pipe Hitbox
			bird->position->x >= p->bottomPipePos->x &&
			bird->position->x <= p->bottomPipePos->x + CoordinateConverter::SizeToWorld(p->pipeSize.x) &&
			bird->position->y <= p->bottomPipePos->y &&
			bird->position->y >= p->bottomPipePos->y - CoordinateConverter::SizeToWorld(p->pipeSize.y))
		{
			std::cout << "hit the bottom" << '\n';
			p->hasBeenHit = true;
			game->gameState = Game::GameState::Dead;
		}
	}
}
void ScoreManager::Dead()
{

}

void ScoreManager::AddScore(int value)
{
	score += value;
	SDL_SetWindowTitle(scoreWindow, std::format("Score: {}", score).c_str());
}