#include "FontHandler.h"

TTF_Font* FontHandler::LoadFont(const char* fileName, int fontSize)
{
    return TTF_OpenFont(fileName, fontSize);
}


void FontHandler::Draw(SDL_Texture* texture, SDL_Rect position)
{
    SDL_RenderCopy(Game::renderer, texture, NULL, &position);
}