// Qore Engine written by Adam Weesner @ 2020
#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityContainer.h"
#include "../AssetHandler.h"
#include "../TextureHandler.h"
#include "TransformComponent.h"

extern EntityContainer entities;

class ColliderComponent: public Component
{
    public:
        ColliderComponent(std::string colliderTag, int x, int y, int width, int height)
        {
            this->colliderTag = colliderTag;
            this->collider = {x, y, width, height};
            this->texture = Game::assetHandler->GetTexture("collision-image");
            this->isRendering = false;
        }


        void Initialize() override
        {
            if (!owner->HasComponent<TransformComponent>()) { return; }
            
            transform = owner->GetComponent<TransformComponent>();
            sourceRect = {0, 0, transform->width, transform->height};
            destRect = {collider.x, collider.y, collider.w, collider.h};
        }


        void Update(float deltaTime) override
        {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;

            destRect.x = collider.x - Game::camera.x;
            destRect.y = collider.y - Game::camera.y;

            IsColliding();
        }


        void Render() override
        {
            if (isRendering)
            {
                TextureHandler::Draw(texture, sourceRect, destRect, SDL_FLIP_NONE);
            }
        }


        void IsColliding()
        {
            SDL_Rect thisCollider = collider;

            for (auto& thatEntity : entities.GetEntities())
            {
                auto thatComponent = thatEntity->GetComponent<ColliderComponent>();

                if (thatComponent && thatComponent != this)
                {
                    auto& thatCollider = thatComponent->collider;

                    if (thisCollider.x + thisCollider.w >= thatCollider.x &&
                        thatCollider.x + thatCollider.w >= thisCollider.x &&
                        thisCollider.y + thisCollider.h >= thatCollider.y &&
                        thatCollider.y + thatCollider.h >= thisCollider.y)
                    {
                        OnCollision(thatComponent);
                    }
                }
            }
        }

        void OnCollision(const ColliderComponent* other)
        {
            owner->OnCollision(other->owner);
        }


        std::string colliderTag;
        SDL_Rect collider;
        SDL_Rect sourceRect;
        SDL_Rect destRect;
        TransformComponent* transform;
        SDL_Texture* texture;
        bool isRendering;
};

#endif