// Qore Engine written by Adam Weesner @ 2020
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include "./EntityContainer.h"
#include "./Component.h"

// Forward declarations
class EntityContainer;
class Component;

class Entity
{
    public:
        Entity(EntityContainer& newEntityContainer);
        Entity(EntityContainer& newEntityContainer, std::string newName);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;
        std::string PrintComponents();

        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args) {
            T* newComponent(new T(std::forward<TArgs>(args)...));

            newComponent->owner = this;
            components.emplace_back(newComponent);
            newComponent->Initialize();
            
            return *newComponent;
        }

        std::string name;

    private:
        EntityContainer& entityContainer;
        std::vector<Component*> components;
        bool isActive;
};

#endif