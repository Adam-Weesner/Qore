// Qore Engine written by Adam Weesner @ 2020
#ifndef EMITTERCOMPONENT_H
#define EMITTERCOMPONENT_H

#include "../../lib/glm/glm.hpp"
#include "../EntityContainer.h"
#include "TransformComponent.h"

class EmitterComponent: public Component
{
    public:
        EmitterComponent(float speed, float range, float angleDeg, bool isLooping)
        {
            this->speed = speed;
            this->range = range;
            this->angleRad = glm::radians(angleDeg);
            this->isLooping = isLooping;
        }


        void Initialize() override
        {
            if (!owner->HasComponent<TransformComponent>()) { return; }

            transform = owner->GetComponent<TransformComponent>();
            origin = glm::vec2(transform->position.x, transform->position.y);
            transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
        }


        void Update(float deltaTime) override 
        {
            if(glm::distance(transform->position, origin) > range)
            {
                if (isLooping)
                {
                    transform->position.x = origin.x;
                    transform->position.y = origin.y;
                }
                else
                {
                    owner->Destroy();
                }
            }
        }


    private:
        TransformComponent* transform;
        glm::vec2 origin;
        float speed;
        float range;
        float angleRad;
        bool isLooping;
};

#endif