#pragma once
#include <SDL3/SDL.h>
#include "Vector2.h"
#include "Game.h"

class Pipe
{
public:
	bool hasScored = false;
	Vector2 pipeSize = Vector2(200, 800);
	Vector2 middlePos = Vector2(9, 0);
	Vector2* topPipePos;
	Vector2* bottomPipePos;
	SDL_Window* topPipe;
	SDL_Window* bottomPipe;
	SDL_Renderer* pipeRendererTop;
	SDL_Renderer* pipeRendererBottom;
	float speed = -10;
	float holeDistance = 2;
	Game* game;
	

	void Tick();
	Pipe(Game* game, float middleHight = 0, float holeDistance = 2);
	const void DestroyWindows();
};