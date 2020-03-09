#include "AssetHandler.h"
#include "Components/TransformComponent.h"

AssetHandler::AssetHandler(EntityContainer* newEntities)
{

}


AssetHandler::~AssetHandler()
{

}


void AssetHandler::ClearData()
{
    textures.clear();
}


void AssetHandler::AddTexture(std::string textureID, const char* filePath)
{
    textures.emplace(textureID, TextureHandler::LoadTexture(filePath));
}


SDL_Texture* AssetHandler::GetTexture(std::string textureID)
{
    return textures[textureID];
}

