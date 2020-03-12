// Qore Engine written by Adam Weesner @ 2020
#include "LoadLua.h"
#include "Constants.h"
#include "AssetHandler.h"
#include "Map.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/InputComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/LabelComponent.h"
#include "Components/EmitterComponent.h"
#include "Player.h"


LoadLua::LoadLua()
{
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
}


void LoadLua::LoadLevel(int levelNum)
{
    // Loads assets from Lua config file
    std::string levelName = "Level" + std::to_string(levelNum);
    lua.script_file("assets/scripts/" + levelName + ".lua");

    levelData = lua[levelName];

    LoadAssets();
    LoadMap();
    LoadEntities();
}


void LoadLua::LoadAssets()
{
    sol::table levelAssets = levelData["assets"];
    bool isDoneLoading = true;

    for (int i = 0; isDoneLoading; i++)
    {
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[i];

        // If created table is null, then we have reached the EOF
        if (existsAssetIndexNode == sol::nullopt)
        {
            isDoneLoading = false;
        }
        else
        {
            sol::table asset = levelAssets[i];
            std::string assetType = asset["type"];
            
            if (assetType.compare("texture") == 0)
            {
                std::string textureID = asset["id"];
                std::string filePath = asset["file"];
                Game::assetHandler->AddTexture(textureID, filePath.c_str());
            } 
            else if (assetType.compare("font") == 0)
            {
                std::string textureID = asset["id"];
                std::string filePath = asset["file"];
                int fontSize = asset["fontSize"];
                Game::assetHandler->AddFont(textureID, filePath.c_str(), fontSize);
            } 
        }
    }
}


void LoadLua::LoadMap()
{
    sol::table levelMap = levelData["map"];
    std::string mapTextureID = levelMap["textureAssetID"];
    std::string mapFile = levelMap["file"];

    Map* map = new Map(
        mapTextureID,
        static_cast<int>(levelMap["scale"]),
        static_cast<int>(levelMap["tileSize"])
    );

    map->LoadMap(
        mapFile, 
        static_cast<int>(levelMap["mapSizeX"]), 
        static_cast<int>(levelMap["mapSizeY"])
    );
}


void LoadLua::LoadEntities()
{
    sol::table levelEntities = levelData["entities"];
    bool isDoneLoading = true;

    for (int i = 0; isDoneLoading; i++)
    {
        sol::optional<sol::table> existsAssetIndexNode = levelEntities[i];

        // If created table is null, then we have reached the EOF
        if (existsAssetIndexNode == sol::nullopt)
        {
            isDoneLoading = false;
        }
        else
        {
            sol::table entity = levelEntities[i];
            std::string name = entity["name"];
            int layer = static_cast<int>(entity["layer"]);
            
            Entity* newEntity = new Entity(name, Layers(layer));

            if (name.compare("player") == 0)
            {
                newEntity = new Player(name, Layers(layer));
                Game::player = dynamic_cast<Player*>(newEntity);
            } 
            
            // Add transform component
            sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
            if (existsTransformComponent != sol::nullopt)
            {
                newEntity->AddComponent<TransformComponent>
                (
                    static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                    static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                    static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
                    static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
                    static_cast<int>(entity["components"]["transform"]["width"]),
                    static_cast<int>(entity["components"]["transform"]["height"]),
                    static_cast<int>(entity["components"]["transform"]["scale"])
                );
            }

            // Add sprite component
            sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
            if (existsSpriteComponent != sol::nullopt) 
            {
                std::string textureID = entity["components"]["sprite"]["textureAssetID"];
                bool isAnimated = entity["components"]["sprite"]["animated"];

                if (isAnimated) 
                {
                    newEntity->AddComponent<SpriteComponent>
                    (
                        textureID.c_str(),
                        static_cast<int>(entity["components"]["sprite"]["frameCount"]),
                        static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
                        static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
                        static_cast<bool>(entity["components"]["sprite"]["fixed"])
                    );
                } else 
                {
                    newEntity->AddComponent<SpriteComponent>(textureID.c_str());
                }
            }

            // Add input component
            sol::optional<sol::table> existsInputComponent = entity["components"]["input"];
            if (existsInputComponent != sol::nullopt) 
            {
                sol::optional<sol::table> existsInputComponent = entity["components"]["input"]["keyboard"];
                if (existsInputComponent != sol::nullopt) 
                {
                    std::string upKey = entity["components"]["input"]["keyboard"]["up"];
                    std::string rightKey = entity["components"]["input"]["keyboard"]["right"];
                    std::string downKey = entity["components"]["input"]["keyboard"]["down"];
                    std::string leftKey = entity["components"]["input"]["keyboard"]["left"];
                    std::string shootKey = entity["components"]["input"]["keyboard"]["shoot"];
                    newEntity->AddComponent<InputComponent>(upKey, rightKey, downKey, leftKey, shootKey);
                }
            }

            // Add collider component
            sol::optional<sol::table> existsColliderComponent = entity["components"]["collider"];
            if (existsColliderComponent != sol::nullopt) 
            {
                newEntity->AddComponent<ColliderComponent>();
            }

            // Add emitter component
            sol::optional<sol::table> existsProjectileEmitterComponent = entity["components"]["projectileEmitter"];
            if (existsProjectileEmitterComponent != sol::nullopt) 
            {
                int parentEntityXPos = entity["components"]["transform"]["position"]["x"];
                int parentEntityYPos = entity["components"]["transform"]["position"]["y"];
                int parentEntityWidth = entity["components"]["transform"]["width"];
                int parentEntityHeight = entity["components"]["transform"]["height"];
                int projectileWidth = entity["components"]["projectileEmitter"]["width"];
                int projectileHeight = entity["components"]["projectileEmitter"]["height"];
                int projectileSpeed = entity["components"]["projectileEmitter"]["speed"];
                int projectileRange = entity["components"]["projectileEmitter"]["range"];
                int projectileAngle = entity["components"]["projectileEmitter"]["angle"];
                bool projectileShouldLoop = entity["components"]["projectileEmitter"]["shouldLoop"];

                std::string textureAssetID = entity["components"]["projectileEmitter"]["textureAssetID"];
                Entity* projectile = new Entity("projectile", PROJECTILE_LAYER);

                projectile->AddComponent<TransformComponent>
                (
                    parentEntityXPos + (parentEntityWidth / 2),
                    parentEntityYPos + (parentEntityHeight / 2),
                    0,
                    0,
                    projectileWidth,
                    projectileHeight,
                    1
                );

                projectile->AddComponent<SpriteComponent>(textureAssetID.c_str());

                projectile->AddComponent<EmitterComponent>
                (
                    projectileSpeed,
                    projectileAngle,
                    projectileRange,
                    projectileShouldLoop
                );

                projectile->AddComponent<ColliderComponent>( );
            }
        }
    }
}