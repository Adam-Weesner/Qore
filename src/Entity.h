// QORE Engine written by Adam Weesner @ 2020
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>

// Forward declarations
class Component;
class EntityContainer;

class Entity
{
    public:
        std::string name;
        Entity(EntityContainer& entities);
        Entity(EntityContainer& manager, std::string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool isActive() const;

    private:
        EntityContainer& entities;
        std::vector<Component*> components;
        bool isActive;
};

#endif