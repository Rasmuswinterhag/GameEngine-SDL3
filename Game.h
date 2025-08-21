#pragma once
#include <SDL3/SDL.h>
#include "CoordinateConverter.h"
class Bird;
class PipeManager;
class ScoreManager;

class Game
{
	
	struct FrameData {
		int framecnt = 0;
		const Uint32 frameDelay = 1000 / 60;
		Uint32 frameStart = 0;
		Uint32 frameTime = 0;
		Uint64 lastTime = 0;
		float timeScale = 1.f;
		float deltaTime = 0;
		float scaledDeltaTime = 0;

	};

public:
	Game();
	~Game();
	bool Init();
	void HandleEvents();
	void Update();
	void Render();
	void Quit();

	bool running;
	FrameData fdata;

	Bird* bird;
	SDL_Renderer* birdRenderer;
	SDL_Texture* birdTexture;
	PipeManager* pipeManager;
	ScoreManager* scoreManager;
};