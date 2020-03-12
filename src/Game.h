// Qore Engine written by Adam Weesner @ 2020
#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Component.h"
#include "EntityContainer.h"
#include "Player.h"
#include "LoadLua.h"

class AssetHandler;

class Game
{
    public:
        Game();
        ~Game();
        void Initialize(const int winWidth, const int winHeight);
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();

        bool IsRunning() const;
        void HandleCameraMovement();

        static SDL_Renderer* renderer;
        static SDL_Event event;
        static SDL_Rect camera;
        static AssetHandler* assetHandler;
        static Player* player;
        float deltaTime;
        
    private:
        bool isRunning;
        Uint32 ticksLastFrame;
        SDL_Window *window;
        LoadLua* lua;
};
#endif