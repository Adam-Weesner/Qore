// Qore Engine written by Adam Weesner @ 2020
#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Entity.h"
#include "Component.h"
#include "EntityContainer.h"

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

        void LoadLevel(int levelNum);
        bool IsRunning() const;
        void HandleCameraMovement();

        static SDL_Renderer* renderer;
        static SDL_Event event;
        static SDL_Rect camera;
        static AssetHandler* assetHandler;
        float deltaTime;
        
    private:
        bool isRunning;
        Uint32 ticksLastFrame;
        SDL_Window *window;
};
#endif