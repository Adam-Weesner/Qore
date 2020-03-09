// Qore Engine written by Adam Weesner @ 2020
#include <fstream>
#include "Game.h"
#include "Map.h"
#include "EntityContainer.h"
#include "Components/TileComponent.h"

extern EntityContainer entities;

Map::Map(std::string textureID, int scale, int tileSize)
{
    this->textureID = textureID;
    this->scale = scale;
    this->tileSize = tileSize;
}


Map::~Map() { }


void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY)
{
    std::fstream mapFile;
    mapFile.open(filePath);

    for (int y = 0; y < mapSizeY; y++)
    {
        for (int x = 0; x < mapSizeX; x++)
        {
            char ch;
            mapFile.get(ch);
            int sourceRectY = atoi(&ch) * tileSize;
            mapFile.get(ch);
            int sourceRectX = atoi(&ch) * tileSize;
            AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
            mapFile.ignore();
        }
    }

    mapFile.close();
}


void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y)
{
    Entity& newTile(entities.AddEntity("Tile", TILEMAP_LAYER));
    newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, textureID);
}

