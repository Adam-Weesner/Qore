// Qore Engine written by Adam Weesner @ 2020
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
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
            componentTMap[&typeid(*newComponent)] = newComponent;
            newComponent->Initialize();
            
            return *newComponent;
        }

        template <typename T>
        T* GetComponent() 
        {
            return static_cast<T*>(componentTMap[&typeid(T)]);
        }

        template <typename T>
        bool HasComponent()
        {
            if (componentTMap.count(&typeid(T)))
            {
                return true;
            }

            return false;
        }

        std::string name;

    private:
        EntityContainer& entityContainer;
        std::vector<Component*> components;
        bool isActive;
        std::map<const std::type_info*, Component*> componentTMap;
};

#endif