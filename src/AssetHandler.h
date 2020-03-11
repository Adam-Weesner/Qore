// Qore Engine written by Adam Weesner @ 2020
#ifndef ASSETHANDLER_H
#define ASSETHANDLER_H

#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "TextureHandler.h"
#include "FontHandler.h"
#include "EntityContainer.h"

class AssetHandler
{
    public:
        AssetHandler(EntityContainer* entities);
        ~AssetHandler();
        void ClearData();

        void AddTexture(std::string textureID, const char* filePath);
        SDL_Texture* GetTexture(std::string textureID);

        void AddFont(std::string fontID, const char* filePath, int fontSize);
        TTF_Font* GetFont(std::string fontID);

    private:
        EntityContainer* entities;
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;
};

#endif