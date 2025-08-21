#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include "Game.h"

int main(int argc, char** argv) {

	Game game = Game();
	if (!game.Init()) {
		return -1;
	}

	while (game.running) {
		game.HandleEvents();
		game.Update();
		game.Render();
	}

	game.Quit();
	return 0;
}