// Qore Engine written by Adam Weesner @ 2020
#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Entity.h"
#include "Component.h"
#include "EntityContainer.h"

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

        static SDL_Renderer *renderer;
        float deltaTime;
        
    private:
        bool isRunning;
        Uint32 ticksLastFrame;
        SDL_Window *window;
};
#endif