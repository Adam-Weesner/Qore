// Qore Engine written by Adam Weesner @ 2020
#ifndef KEYBOARDCONTROLCOMPONENT_H
#define KEYBOARDCONTROLCOMPONENT_H

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityContainer.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class KeyboardControlComponent: public Component
{
    public:
        KeyboardControlComponent() {}


        KeyboardControlComponent(std::string upKey,
                                std::string rightKey,
                                std::string downKey,
                                std::string leftKey,
                                std::string shootKey)
        {
            this->upKey = GetSDLKeyStringCode(upKey);
            this->rightKey = GetSDLKeyStringCode(rightKey);
            this->downKey = GetSDLKeyStringCode(downKey);
            this->leftKey = GetSDLKeyStringCode(leftKey);
            this->shootKey = GetSDLKeyStringCode(shootKey);
        }


        void Initialize() override 
        {
            transform = owner->GetComponent<TransformComponent>();
            sprite = owner->GetComponent<SpriteComponent>();
        }


        void Update(float deltaTime) override
        {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);

            if (Game::event.type == SDL_KEYDOWN)
            {
                if (keyCode == upKey)
                {
                    transform->velocity.y = -100;
                    sprite->Play("UpAnimation");
                }
                if (keyCode == rightKey)
                {
                    transform->velocity.x = 100;
                    sprite->Play("RightAnimation");
                }
                if (keyCode == downKey)
                {
                    transform->velocity.y = 100;
                    sprite->Play("DownAnimation");
                }
                if (keyCode == leftKey)
                {
                    transform->velocity.x = -100;
                    sprite->Play("LeftAnimation");
                }
                if (keyCode == shootKey)
                {
                    // TODO shoot key
                }
            }

            if (Game::event.type == SDL_KEYUP)
            {
                if (keyCode == upKey)
                {
                    transform->velocity.y = 0;
                }
                if (keyCode == rightKey)
                {
                    transform->velocity.x = 0;
                }
                if (keyCode == downKey)
                {
                    transform->velocity.y = 0;
                }
                if (keyCode == leftKey)
                {
                    transform->velocity.x = 0;
                }
                if (keyCode == shootKey)
                {
                    // TODO upkey
                }
            }
        }


        std::string GetSDLKeyStringCode(std::string key)
        {
            if (key == "up") return "1073741906";
            if (key == "right") return "1073741903";
            if (key == "down") return "1073741905";
            if (key == "left") return "1073741904";
            if (key == "space") return "32";
            return std::to_string(static_cast<int>(key[0]));
        }


        std::string upKey;
        std::string rightKey;
        std::string downKey;
        std::string leftKey;
        std::string shootKey;
        TransformComponent* transform;
        SpriteComponent* sprite;
};

#endif