// Qore Engine written by Adam Weesner @ 2020
#ifndef ASSETHANDLER_H
#define ASSETHANDLER_H

#include <map>
#include <string>
#include "TextureHandler.h"
#include "EntityContainer.h"

class AssetHandler
{
    public:
        AssetHandler(EntityContainer* newEntities);
        ~AssetHandler();
        void ClearData();
        void AddTexture(std::string textureID, const char* filePath);
        SDL_Texture* GetTexture(std::string textureID);

    private:
        EntityContainer* entities;
        std::map<std::string, SDL_Texture*> textures;
};

#endif