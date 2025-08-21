#include "Pipe.h"
#include "CoordinateConverter.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>

void Pipe::Tick()
{
	if (active) { Move(); }
}

void Pipe::Move()
{
	middlePos.x += speed * game->fdata.deltaTime;

	int h = 0;
	int* topPipeHeight = &h;

	if (SDL_GetWindowSizeInPixels(topPipe, NULL, topPipeHeight))
	{
		topPipePos = new Vector2(middlePos.x, middlePos.y + holeDistance - CoordinateConverter::ToWorldSpace(h));
	}
	CoordinateConverter::SetWindowWorldPosition(topPipe, *(topPipePos));

	bottomPipePos = new Vector2(middlePos.x, middlePos.y - holeDistance);
	CoordinateConverter::SetWindowWorldPosition(bottomPipe, *(bottomPipePos));
}

Pipe::Pipe(Game* game, float middleHight, float holeDistance)
{
	this->game = game;

	topPipe = SDL_CreateWindow("Pipe", pipeSize.x, pipeSize.y, 0);
	pipeRendererTop = SDL_CreateRenderer(topPipe, NULL);
	bottomPipe = SDL_CreateWindow("Pipe", pipeSize.x, pipeSize.y, 0);
	pipeRendererBottom = SDL_CreateRenderer(bottomPipe, NULL);
	middlePos.y = middleHight;
	this->holeDistance = holeDistance;

	//Rendering
	int w = 0;
	int* width = &w;
	int h = 0;
	int* height = &h;
	SDL_GetWindowSizeInPixels(topPipe, width, height);

	SDL_Texture* pipeTextures[2] = {
	IMG_LoadTexture(pipeRendererTop, "textures/LongPipe.png"),
	IMG_LoadTexture(pipeRendererBottom, "textures/LongPipe.png") };

	SDL_FRect topSquare = { 0, 0, w, pipeTextures[0]->h * (h / 100) };
	SDL_FRect bottomSquare = { 0, 0, w, pipeTextures[1]->h * (h / 100) };
	SDL_RenderTextureRotated(pipeRendererTop, pipeTextures[0], NULL, &topSquare, 180, NULL, SDL_FLIP_NONE);
	SDL_RenderTextureRotated(pipeRendererBottom, pipeTextures[1], NULL, &bottomSquare, 0, NULL, SDL_FLIP_NONE);

	SDL_RenderPresent(pipeRendererTop);
	SDL_RenderPresent(pipeRendererBottom);
}

void Pipe::DeactivateWindow()
{
	active = false;
}

void Pipe::ActivateWindow()
{
	active = true;
}