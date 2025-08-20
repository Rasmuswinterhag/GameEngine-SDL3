#include "PipeManager.h"

PipeManager::PipeManager(Game* game)
{
    this->game = game;
	spawnRate = 100;
    timer = spawnRate; //To spawn a pipe immediately
}

void PipeManager::Tick()
{
    timer += game->fdata.deltaTime;
    if (timer > spawnRate)
    {
        float randomHeight = SDL_rand(7) + minHeight;
        pipes.emplace_back(randomHeight);
        timer -= spawnRate;
    }

        
    for (auto it = pipes.begin(); it != pipes.end(); )
    {
        if (it->middlePos.x > -9)
        {
            it->Tick();
            ++it;
        }
        else
        {
            it->DestroyWindows();
            it = pipes.erase(it); // erase returns the next iterator
        }
    }

}
