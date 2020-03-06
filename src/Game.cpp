// Qore Engine written by Adam Weesner @ 2020
#include <iostream>
#include "Constants.h"
#include "Game.h"

EntityContainer entities;
SDL_Renderer* Game::renderer;

Game::Game()
{
    isRunning = false;
}


Game::~Game()
{

}


void Game::Initialize(const int winWidth, const int winHeight)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "ERROR initializing SDL." << std::endl;
        return;
    }
    
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        winWidth,
        winHeight,
        SDL_WINDOW_BORDERLESS
    );

    if (!window)
    {
        std::cerr << "ERROR initializing SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        std::cerr << "ERROR initializing SDL renderer." << std::endl;
        return;
    }

    isRunning = true;
}


void Game::ProcessInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT: 
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            break;
        default:
            break;
    }
}


void Game::Update()
{
    // Wait until 16.6ms has ellasped since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

    // Difference in ticks from last frame, converted into seconds
    deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a max value. Prevents breakpoint overload
    deltaTime = (deltaTime > DELTA_MAX) ? DELTA_MAX : deltaTime;

    // Gets the number of miliseconds since SDL was initialized
    ticksLastFrame = SDL_GetTicks();

    // TODO call manager.update to update all entities as function of deltatime
}


void Game::Render() 
{
    // Set background color
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // TODO call manager.render to render all entities

    SDL_RenderPresent(renderer);
}


void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void LoadLevel(int levelNum)
{

}


bool Game::IsRunning() const
{
    return isRunning;
}