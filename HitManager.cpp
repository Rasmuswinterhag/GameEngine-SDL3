#include "HitManager.h"
#include "CoordinateConverter.h"
#include "PipeManager.h"
#include <string>
#include <iostream>
#include <format>

HitManager::HitManager(Game* game, Bird* bird, PipeManager* pipeManager)
{
	this->game = game;
	this->bird = bird;
	this->pipeManager = pipeManager;

	scoreWindow = SDL_CreateWindow("Score: 0", 400, 0, 0);
	SDL_SetWindowAlwaysOnTop(scoreWindow, true);
	CoordinateConverter::SetWindowWorldPosition(scoreWindow, CoordinateConverter::ToWorldSpace(Vector2Int(CoordinateConverter::screenWidth * 0.425, 50)));
}

void HitManager::Tick()
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

void HitManager::Start() //TODO: optimise to have a function that only runs once
{
	SetScore(0);
}

void HitManager::Playing()
{
	for (Pipe* p : pipeManager->pipes)
	{
		if (!p->hasBeenHit && //Score hitbox
			bird->position->x >= p->middlePos.x &&
			bird->position->x <= p->middlePos.x + CoordinateConverter::SizeToWorldHorizontal(p->pipeSize.x) &&
			bird->position->y >= p->middlePos.y - p->holeDistance &&
			bird->position->y <= p->middlePos.y + p->holeDistance)
		{
			AddScore(1);
			p->hasBeenHit = true;
			
			std::cout << "Scored (" << score << ")" << '\n';
		}
		else if (!p->hasBeenHit && //top pipe Hitbox
			bird->position->x >= p->topPipePos->x &&
			bird->position->x <= p->topPipePos->x + CoordinateConverter::SizeToWorldHorizontal(p->pipeSize.x) &&
			bird->position->y <= p->topPipePos->y &&
			bird->position->y >= p->topPipePos->y - CoordinateConverter::SizeToWorldVertical(p->pipeSize.y))
		{
			std::cout << "Hit the top" << '\n';
			p->hasBeenHit = true;
			game->SetGameState(Game::GameState::Dead);
		}
		else if (!p->hasBeenHit && //bottom pipe Hitbox
			bird->position->x >= p->bottomPipePos->x &&
			bird->position->x <= p->bottomPipePos->x + CoordinateConverter::SizeToWorldHorizontal(p->pipeSize.x) &&
			bird->position->y <= p->bottomPipePos->y &&
			bird->position->y >= p->bottomPipePos->y - CoordinateConverter::SizeToWorldVertical(p->pipeSize.y))
		{
			std::cout << "Hit the bottom" << '\n';
			p->hasBeenHit = true;
			game->SetGameState(Game::GameState::Dead);
		}
	}
}
void HitManager::Dead()
{

}

void HitManager::AddScore(int value)
{
	score += value;
	SDL_SetWindowTitle(scoreWindow, std::format("Score: {}", score).c_str());
}

void HitManager::SetScore(int value)
{
	score = value;
	SDL_SetWindowTitle(scoreWindow, std::format("Score: {}", score).c_str());
}