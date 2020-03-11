#ifndef LABELCOMPONENT_H
#define LABELCOMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../FontHandler.h"
#include "../EntityContainer.h"
#include "../AssetHandler.h"
#include "../Game.h"

class LabelComponent: public Component
{
    public:
        LabelComponent(int x, int y, std::string text, std::string fontFamily, SDL_Color color)
        {
            this->position.x = x;
            this->position.y = y;
            this->text = text;
            this->fontFamily = fontFamily;
            this->color = color;

            SetText(text, fontFamily);
        }


        void SetText(std::string text, std::string fontFamily)
        {
            SDL_Surface* surface = TTF_RenderText_Blended(Game::assetHandler->GetFont(fontFamily), text.c_str(), color);
            texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
            SDL_FreeSurface(surface);
            SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
        }


        void Render() override
        {
            FontHandler::Draw(texture, position);
        }


    private:
        SDL_Rect position;
        std::string text;
        std::string fontFamily;
        SDL_Color color;
        SDL_Texture* texture;
};

#endif