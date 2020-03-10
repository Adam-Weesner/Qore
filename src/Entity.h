// Qore Engine written by Adam Weesner @ 2020
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "Constants.h"
#include "EntityContainer.h"
#include "Component.h"

// Forward declarations
class EntityContainer;
class Component;

class Entity
{
    public:
        Entity();
        Entity(std::string name, Layers layer);
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
            return componentTMap.count(&typeid(T));
        }


        virtual void OnCollision(const Entity* other) { }

        std::string name;
        Layers layer;

    protected:
        EntityContainer& entityContainer;
        std::vector<Component*> components;
        bool isActive;
        std::map<const std::type_info*, Component*> componentTMap;
};

#endif