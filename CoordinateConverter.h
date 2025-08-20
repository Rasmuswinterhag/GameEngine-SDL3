#pragma once
#include "Vector2.h"
#include <SDL3/SDL.h>
static class CoordinateConverter
{
public:
	static constexpr float worldWidth = 16; //TODO: Get aspect ratio instead of hard code
	static constexpr float worldHeight = 9; //TODO: Get aspect ratio instead of hard code
	static const int screenWidth = 2560; //TODO: Get the height instead of hard code
	static const int screenHeight = 1600; //TODO: Get the height instead of hard code

	static Vector2Int ToScreenSpace(Vector2 WorldSpace);
	static int ToScreenSpace(int WorldSpace);

	static Vector2 ToWorldSpace(Vector2Int ScreenSpace);
	static float ToWorldSpace(int ScreenSpace);

	static void SetWindowWorldPosition(SDL_Window* window, Vector2 worldPosition);
	
	static float Lerp(float a, float b, float t);
	static float InverseLerp(float a, float b, float v);
};