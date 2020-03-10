// Qore Engine written by Adam Weesner @ 2020
#include "Collision.h"

bool Collision::IsColliding(const SDL_Rect rectA, const SDL_Rect rectB)
{
    return (
        rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y
    );
}