#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Bird.h"
#include "PipeManager.h"
#include "ScoreManager.h"

Game::Game() {}
Game::~Game() {}

bool Game::Init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) == 0) {
		std::cerr << "Init Error: " << SDL_GetError() << "\n";
		return false;
	}

	//Create Game Objects
	bird = new Bird(this);
	pipeManager = new PipeManager(this);
	scoreManager = new ScoreManager(this, bird, pipeManager);

	//Rendering Prep
	birdRenderer = SDL_CreateRenderer(bird->window, NULL);
	birdTexture = IMG_LoadTexture(birdRenderer, "textures/Bird.png");

	running = true;
	return true;
}

void Game::HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_EVENT_QUIT:
			running = false;
			break;
		case SDL_EVENT_KEY_DOWN:
			if (event.key.key == SDLK_ESCAPE) { running = false; }
			break;
		}
	}
}

void Game::Update() {
	Uint64 now = SDL_GetTicks();
	fdata.deltaTime = (now - fdata.lastTime) / 1000.0f; //seconds
	fdata.lastTime = now;

	//Time scale
	fdata.scaledDeltaTime = fdata.deltaTime * fdata.timeScale;


	//delay to fps target
	fdata.frameStart = SDL_GetTicks();
	fdata.framecnt++;

	fdata.frameTime = SDL_GetTicks() - fdata.frameStart;

	if (fdata.frameTime < fdata.frameDelay) {
		SDL_Delay(fdata.frameDelay - fdata.frameTime);
	}

	//Tick Objects
	bird->Tick();
	pipeManager->Tick();
	scoreManager->Tick();
}

void Game::Render() {

	//Rendering
	SDL_RenderClear(birdRenderer);

	//Render Bird
	SDL_FRect square = { 0, 0, 100, 100 };
	float birdAngle = -bird->velocity * 10;
	if (birdAngle > 90) { birdAngle = 90; }
	SDL_RenderTextureRotated(birdRenderer, birdTexture, NULL, &square, birdAngle, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(birdRenderer);
}

void Game::Quit() {
	std::cerr << "Quit Game" << "\n";
	SDL_DestroyWindow(bird->window);
	SDL_Quit();
}

