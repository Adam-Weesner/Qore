#include "AssetHandler.h"
#include "Components/TransformComponent.h"

AssetHandler::AssetHandler(EntityContainer* entities)
{

}


AssetHandler::~AssetHandler()
{

}


void AssetHandler::ClearData()
{
    textures.clear();
    fonts.clear();
}


void AssetHandler::AddTexture(std::string textureID, const char* filePath)
{
    textures.emplace(textureID, TextureHandler::LoadTexture(filePath));
}


SDL_Texture* AssetHandler::GetTexture(std::string textureID)
{
    return textures[textureID];
}


void AssetHandler::AddFont(std::string fontID, const char* filePath, int fontSize)
{
    fonts.emplace(fontID, FontHandler::LoadFont(filePath, fontSize));
}


TTF_Font* AssetHandler::GetFont(std::string fontID)
{
    return fonts[fontID];
}