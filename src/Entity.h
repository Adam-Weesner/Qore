// Qore Engine written by Adam Weesner @ 2020
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
        Entity(EntityContainer& newEntityContainer);
        Entity(EntityContainer& newEntityContainer, std::string newName);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;

        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args);

        std::string name;

    private:
        EntityContainer& entityContainer;
        std::vector<Component*> components;
        bool isActive;
};

#endif