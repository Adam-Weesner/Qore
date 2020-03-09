// Qore Engine written by Adam Weesner @ 2020
#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include "../Constants.h"
#include "../EntityContainer.h"
#include "../../lib/glm/glm.hpp"
#include "../Game.h"

class TransformComponent: public Component
{
    public:
        TransformComponent(int posX, int posY, int velX, int velY, int newWidth, int newHeight, int newScale)
        {
            position = glm::vec2(posX, posY);
            velocity = glm::vec2(velX, velY);
            width = newWidth;
            height = newHeight;
            scale = newScale;
        }


        void Update(float deltaTime) override
        {
            auto newPosX = position.x + velocity.x * deltaTime;
            auto newPosY = position.y + velocity.y * deltaTime;
            position.x = glm::clamp(newPosX, 0.0f, (float)WINDOW_WIDTH);
            position.y = glm::clamp(newPosY, 0.0f, (float)WINDOW_HEIGHT);
        }

        glm::vec2 position;
        glm::vec2 velocity;
        int width;
        int height;
        int scale;
};

#endif