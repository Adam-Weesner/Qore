// Qore Engine written by Adam Weesner @ 2020
#include <iostream>
#include "../lib/glm/glm.hpp"
#include "Constants.h"
#include "Game.h"
#include "AssetHandler.h"
#include "Map.h"
#include "Components/TransformComponent.h"

// Global statics
EntityContainer entities;
AssetHandler* Game::assetHandler = new AssetHandler(&entities);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Player* Game::player;


Game::Game()
{
    isRunning = false;
    lua = new LoadLua();
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

    if (TTF_Init() != 0)
    {
        std::cerr << "ERROR intializing TTF" << std::endl;
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

    lua->LoadLevel(0);

    isRunning = true;
}


void Game::ProcessInput()
{
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

    entities.Update(deltaTime);

    HandleCameraMovement();
}


void Game::Render() 
{
    // Set background color
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (!entities.IsEmpty()) 
    { 
        entities.Render();
    }

    SDL_RenderPresent(renderer);
}


void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


bool Game::IsRunning() const
{
    return isRunning;
}


void Game::HandleCameraMovement()
{
    TransformComponent* playerTransform = player->GetComponent<TransformComponent>();

    camera.x = playerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = playerTransform->position.y - (WINDOW_HEIGHT / 2);

    // Clamp camera values to screen height/width
    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}