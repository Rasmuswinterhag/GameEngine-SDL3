#pragma once
#include <SDL3/SDL.h>
#include "Vector2.h"
#include "Game.h"

class Pipe
{
	Vector2 startPos = Vector2(9, 0);
public:
	float holeDistance = 1; //this is the default hole distance, can be overridden when spawning in/resetting
	bool active = true;
	bool hasBeenHit = false;
	Vector2 pipeSize = Vector2(200, 1600);
	Vector2 middlePos = Vector2(0, 0);
	Vector2* topPipePos;
	Vector2* bottomPipePos;
	SDL_Window* topPipe;
	SDL_Window* bottomPipe;
	SDL_Renderer* pipeRendererTop;
	SDL_Renderer* pipeRendererBottom;
	float speed = -5;
	Game* game;
	

	void Tick();
	void Move();
	Pipe(Game* game, float middleHight = 0, float holeDistance = 0);
	void DeactivateWindow();
	void ActivateWindow();
	void ResetPipe(float middleHight = 0, float holeDistance = 0);
};