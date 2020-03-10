// Qore Engine written by Adam Weesner @ 2020
#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>

class Collision
{
    public:
        static bool IsColliding(const SDL_Rect rectA, const SDL_Rect rectB);
};

#endif