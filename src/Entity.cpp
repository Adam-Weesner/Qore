// Qore Engine written by Adam Weesner @ 2020
#include "Component.h"
#include "Entity.h"


Entity::Entity(EntityContainer& newEntityContainer):
    entityContainer(newEntityContainer)
{
    isActive = true;
}

Entity::Entity(EntityContainer& newEntityContainer, std::string newName):
    entityContainer(newEntityContainer)
{
    name = newName;
    isActive = true;
}


void Entity::Update(float deltaTime)
{
    for(auto& component : components)
    {
        component->Update(deltaTime);
    }
}


void Entity::Render()
{
    for(auto& component : components)
    {
        component->Render();
    }
    
}


void Entity::Destroy()
{
    isActive = false;
}


bool Entity::IsActive() const
{
    return isActive;
}


template <typename T, typename... TArgs>
T& AddComponent(TArgs&&... args)
{
    T* newComponent(new T(std::forward<TArgs>(args)...));

    newComponent->owner = this;
    components.emplace_back(newComponent);
    newComponent->Initialize();
    
    return *newComponent;
}