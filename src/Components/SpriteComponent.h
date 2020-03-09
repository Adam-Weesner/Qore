// Qore Engine written by Adam Weesner @ 2020
#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../TextureHandler.h"
#include "../AssetHandler.h"

class SpriteComponent: public Component {
    public:
        SpriteComponent(const char* filePath)
        {
            SetTexture(filePath);
        }

        void Initialize() override
        {
            // Create transform component if none exists
            if (!owner->HasComponent<TransformComponent>())
            {
                owner->AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
            }

            transform = owner->GetComponent<TransformComponent>();
           
            sourceRect.x = 0;
            sourceRect.y = 0;
            sourceRect.w = transform->width;
            sourceRect.h = transform->height;
        }

        void Update(float deltaTime) override
        {
            destRect.x = (int) transform->position.x;
            destRect.y = (int) transform->position.y;
            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;
        }

        void Render() override
        {
            TextureHandler::Draw(texture, sourceRect, destRect, spriteFlip);
        }

        void SetTexture(std::string assetTextureID)
        {
            texture = Game::assetHandler->GetTexture(assetTextureID);
        }

        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRect;
        SDL_Rect destRect;
};

#endif