// QORE Engine written by Adam Weesner @ 2020
#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/glm/glm.hpp"

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

        float deltaTime;
        
    private:
        bool isRunning;
        Uint32 ticksLastFrame;

        SDL_Window *window;
        SDL_Renderer *renderer;
        
        glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
        glm::vec2 projectileVel = glm::vec2(20.0f, 30.0f);
};
#endif