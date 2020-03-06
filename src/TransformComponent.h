#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "EntityContainer.h"
#include "../../lib/glm/glm.hpp"

class TransformComponent: Component
{
    public:
        TransformComponent(int posX, int posY, int velX, int velY, int newWidth, int newHeight, int newScale);
        void Initialize();
        void Update(float deltaTime) override;
        void Render() override;

        glm::vec2 position;
        glm::vec2 velocity;
        int width;
        int height;
        int scale;

    private:
};

#endif