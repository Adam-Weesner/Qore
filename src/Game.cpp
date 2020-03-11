// Qore Engine written by Adam Weesner @ 2020
#include <iostream>
#include "../lib/glm/glm.hpp"
#include "Constants.h"
#include "Game.h"
#include "AssetHandler.h"
#include "Map.h"
#include "Player.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/LabelComponent.h"
#include "Components/EmitterComponent.h"

// Global statics
EntityContainer entities;
AssetHandler* Game::assetHandler = new AssetHandler(&entities);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;
Player* player;


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
    //CheckCollisions();
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


void Game::LoadLevel(int levelNum)
{
    // Start including new assets to the assetmanager list
    assetHandler->AddTexture("collision-image", "assets/images/collision-texture.png");
    assetHandler->AddTexture("tank-image", "assets/images/tank-big-right.png");
    assetHandler->AddTexture("chopper-image", "assets/images/chopper-spritesheet.png");
    assetHandler->AddTexture("radar-image", "assets/images/radar.png");
    assetHandler->AddTexture("jungle-tile", "assets/tilemaps/jungle.png");
    assetHandler->AddTexture("heliport", "assets/images/heliport.png");
    assetHandler->AddTexture("projectile", "assets/images/bullet-enemy.png");
    assetHandler->AddFont("charriot-font", "assets/fonts/charriot.ttf", 14);

    map = new Map("jungle-tile", 3, 32);
    map->LoadMap("assets/tilemaps/jungle.map", 25, 20);

    // Start including entities and also components to them
    player = new Player("player", PLAYER_LAYER);
    player->AddComponent<TransformComponent>(240, 160, 0, 0, 32, 32, 1);
    player->AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    player->AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");    
    player->AddComponent<ColliderComponent>();
    
    Entity* tank = new Entity("tank", ENEMY_LAYER);
    tank->AddComponent<TransformComponent>(150, 495, 0, 0, 32, 32, 1);
    tank->AddComponent<SpriteComponent>("tank-image"); 
    tank->AddComponent<ColliderComponent>();

    Entity* projectile = new Entity("projectile", PROJECTILE_LAYER);
    projectile->AddComponent<TransformComponent>(150+16, 495+16, 10, 0, 4, 4, 1);
    projectile->AddComponent<SpriteComponent>("projectile");
    projectile->AddComponent<ColliderComponent>();
    projectile->AddComponent<EmitterComponent>(50, 200, 270, true);
    
    Entity* radar = new Entity("radar", UI_LAYER);
    radar->AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radar->AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

    Entity* heliport = new Entity("heliport", ENVIRONMENT_LAYER);
    heliport->AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
    heliport->AddComponent<SpriteComponent>("heliport");
    heliport->AddComponent<ColliderComponent>();
    
    Entity* labelLevelName = new Entity("LabelLevelName", UI_LAYER);
    labelLevelName->AddComponent<LabelComponent>(10, 10, "First Level", "charriot-font", WHITE_COLOR);
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