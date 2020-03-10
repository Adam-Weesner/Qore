// Qore Engine written by Adam Weesner @ 2020
#include <iostream>
#include "../lib/glm/glm.hpp"
#include "Constants.h"
#include "Game.h"
#include "AssetHandler.h"
#include "Map.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/ColliderComponent.h"

// Global statics
EntityContainer entities;
AssetHandler* Game::assetHandler = new AssetHandler(&entities);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;


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

    LoadLevel(0);

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
    CheckCollisions();
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


Entity& player(entities.AddEntity("chopper", PLAYER_LAYER));

void Game::LoadLevel(int levelNum)
{
    // Start including new assets to the assetmanager list
    assetHandler->AddTexture("tank-image", "assets/images/tank-big-right.png");
    assetHandler->AddTexture("chopper-image", "assets/images/chopper-spritesheet.png");
    assetHandler->AddTexture("radar-image", "assets/images/radar.png");
    assetHandler->AddTexture("jungle-tile", "assets/tilemaps/jungle.png");

    map = new Map("jungle-tile", 3, 32);
    map->LoadMap("assets/tilemaps/jungle.map", 25, 20);

    // Start including entities and also components to them
    player.AddComponent<TransformComponent>(240, 160, 0, 0, 32, 32, 1);
    player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");    
    player.AddComponent<ColliderComponent>("player", 240, 106, 32, 32);
    
    Entity& tank(entities.AddEntity("tank", ENEMY_LAYER));
    tank.AddComponent<SpriteComponent>("tank-image"); 
    tank.AddComponent<ColliderComponent>("enemy", 240, 106, 32, 32);
    

    Entity& radar(entities.AddEntity("radar", UI_LAYER));
    radar.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radar.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

    //std::cout << entities.PrintEntities();
}


bool Game::IsRunning() const
{
    return isRunning;
}


void Game::HandleCameraMovement()
{
    TransformComponent* playerTransform = player.GetComponent<TransformComponent>();

    camera.x = playerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = playerTransform->position.y - (WINDOW_HEIGHT / 2);

    // Clamp camera values to screen height/width
    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}


void Game::CheckCollisions()
{
    std::string collisionTagType = entities.CheckEntityCollisions(player);

    if (collisionTagType.compare("enemy") == 0)
    {
        isRunning = false;
    }
}