#include "CoordinateConverter.h"

	Vector2Int CoordinateConverter::ToScreenSpace(Vector2 WorldSpace)
	{
		return Vector2Int(
		(int)Lerp(0, screenWidth, InverseLerp(-worldWidth / 2, worldWidth / 2, WorldSpace.x)),
		(int)Lerp(screenHeight, 0, InverseLerp(-worldHeight / 2, worldHeight / 2, WorldSpace.y))
		);
	}

	int CoordinateConverter::ToScreenSpace(int WorldSpace)
	{
		return int ((int)Lerp(0, screenWidth, InverseLerp(-worldWidth / 2, worldWidth / 2, WorldSpace)));
	}

	Vector2 CoordinateConverter::ToWorldSpace(Vector2Int ScreenSpace)
	{
		return Vector2(
			Lerp(-worldWidth / 2, worldWidth / 2, InverseLerp(0, screenWidth, ScreenSpace.x)),
			Lerp(-worldHeight / 2, worldHeight / 2, InverseLerp(screenHeight, 0, ScreenSpace.y))
		);
	}

	float CoordinateConverter::SizeToWorld(int screenSize)
	{
		return (float)screenSize / screenWidth * worldWidth;
	}


	void CoordinateConverter::SetWindowWorldPosition(SDL_Window* window, Vector2 worldPosition)
	{
		Vector2Int* screenPos = new Vector2Int(ToScreenSpace(worldPosition));
		SDL_SetWindowPosition(window, screenPos->x, screenPos->y);
	}

	float CoordinateConverter::Lerp(float a, float b, float t)
	{
		return (float)(a + (b - a) * t);
	}

	float CoordinateConverter::InverseLerp(float a, float b, float v)
	{
		return (v - a) / ((float)b - a);
	}
