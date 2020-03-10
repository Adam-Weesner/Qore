// Qore Engine written by Adam Weesner @ 2020
#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../TextureHandler.h"
#include "../AssetHandler.h"
#include "../Animation.h"

class SpriteComponent: public Component {
    public:
        SpriteComponent(const char* filePath)
        {
            this->isAnimated = false;
            this->isFixed = false;
            this->animationIndex = 0;
            SetTexture(filePath);
        }


        SpriteComponent(const char* filePath, int numFrames, int animationSpeed, bool hasDirections, bool isFixed)
        {
            this->isAnimated = true;
            this->numFrames = numFrames;
            this->isFixed = isFixed;
            this->animationSpeed = animationSpeed;
            this->animationIndex = 0;

            if (hasDirections)
            {
                Animation downAnim = Animation(0, numFrames, animationSpeed);
                Animation rightAnim = Animation(1, numFrames, animationSpeed);
                Animation leftAnim = Animation(2, numFrames, animationSpeed);
                Animation upAnim = Animation(3, numFrames, animationSpeed);

                animations.emplace("DownAnimation", downAnim);
                animations.emplace("RightAnimation", rightAnim);
                animations.emplace("LeftAnimation", leftAnim);
                animations.emplace("UpAnimation", upAnim);

                this->animationIndex = 0;
                this->currentAnimationName = "DownAnimation";
            }
            else
            {
                Animation singleAnimation = Animation(0, numFrames, animationSpeed);
                animations.emplace("SingleAnimation", singleAnimation);
                animationIndex = 0;
                currentAnimationName = "SingleAnimation";
            }

            Play(this->currentAnimationName);
            
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
            if (isAnimated)
            {
                sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
            }

            sourceRect.y = animationIndex * transform->height;

            // If fixed, then disable camera influence
            auto cameraX = isFixed ? 0 : Game::camera.x;
            auto cameraY = isFixed ? 0 : Game::camera.y;

            destRect.x = static_cast<int>(transform->position.x) - cameraX;
            destRect.y = static_cast<int>(transform->position.y) - cameraY;
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


        void Play(std::string animationName)
        {
            auto& anim = animations[animationName];
            numFrames = anim.numFrames;
            animationIndex = anim.index;
            animationSpeed = anim.animationSpeed;
            currentAnimationName = animationName;
        }

        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRect;
        SDL_Rect destRect;
        bool isAnimated;
        bool isFixed;
        int numFrames;
        int animationSpeed;
        unsigned int animationIndex;
        std::string currentAnimationName;
        std::map<std::string, Animation> animations;
};

#endif