#include "CoordinateConverter.h"

int CoordinateConverter::screenWidth = 0;
int CoordinateConverter::screenHeight = 0;

CoordinateConverter::CoordinateConverter()
{
	SDL_DisplayID display = SDL_GetPrimaryDisplay();
	SDL_Rect bounds;
	SDL_GetDisplayBounds(display, &bounds);

	screenWidth = bounds.w;
	screenHeight = bounds.h;
}

Vector2Int CoordinateConverter::ToScreenSpace(Vector2 WorldSpace)
{
	return Vector2Int(
		(int)Lerp(0, screenWidth, InverseLerp(-worldWidth / 2, worldWidth / 2, WorldSpace.x)),
		(int)Lerp(screenHeight, 0, InverseLerp(-worldHeight / 2, worldHeight / 2, WorldSpace.y))
	);
}

int CoordinateConverter::ToScreenSpace(int WorldSpace)
{
	return int((int)Lerp(0, screenWidth, InverseLerp(-worldWidth / 2, worldWidth / 2, WorldSpace)));
}

Vector2 CoordinateConverter::ToWorldSpace(Vector2Int ScreenSpace)
{
	return Vector2(
		Lerp(-worldWidth / 2, worldWidth / 2, InverseLerp(0, screenWidth, ScreenSpace.x)),
		Lerp(-worldHeight / 2, worldHeight / 2, InverseLerp(screenHeight, 0, ScreenSpace.y))
	);
}

float CoordinateConverter::SizeToWorldHorizontal(int screenSize)
{
	return (float)screenSize / screenWidth * worldWidth;
}

float CoordinateConverter::SizeToWorldVertical(int screenSize)
{
	return (float)screenSize / screenHeight * worldHeight;
}


void CoordinateConverter::SetWindowWorldPosition(SDL_Window* window, Vector2 worldPosition)
{
	Vector2Int* screenPos = new Vector2Int(ToScreenSpace(worldPosition));
	SDL_SetWindowPosition(window, screenPos->x, screenPos->y);
}

void CoordinateConverter::SetWindowWorldPositionCentered(SDL_Window* window, Vector2 worldPosition)
{
	int h = 0;
	int* height = &h;
	int w = 0;
	int* width = &w;
	SDL_GetWindowSizeInPixels(window, width, height);

	Vector2Int* screenPos = new Vector2Int(ToScreenSpace(worldPosition));
	screenPos->x -= *width / 2;
	screenPos->y -= *height / 2;
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
