#pragma once
#include "Vector2.h"
#include <SDL3/SDL.h>
class CoordinateConverter
{
public:
	CoordinateConverter();
	static int screenWidth;
	static int screenHeight;
	static constexpr float worldWidth = 16;
	static constexpr float worldHeight = 10;

	static Vector2Int ToScreenSpace(Vector2 WorldSpace);
	static int ToScreenSpace(int WorldSpace);

	static Vector2 ToWorldSpace(Vector2Int ScreenSpace);
	static float SizeToWorldHorizontal(int screenSize);
	static float SizeToWorldVertical(int screenSize);


	static void SetWindowWorldPosition(SDL_Window* window, Vector2 worldPosition);

	static void SetWindowWorldPositionCentered(SDL_Window* window, Vector2 worldPosition);
	
	static float Lerp(float a, float b, float t);
	static float InverseLerp(float a, float b, float v);
};