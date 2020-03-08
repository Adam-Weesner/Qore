// Qore Engine written by Adam Weesner @ 2020
#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include "Game.h";

class TextureHandler
{
    public:
        static SDL_Texture* LoadTexture(const char* filePath);
        static void Draw(
            SDL_Texture* texture, 
            SDL_Rect sourceRect, 
            SDL_Rect destRect, 
            SDL_RendererFlip flip
        );
};

#endif