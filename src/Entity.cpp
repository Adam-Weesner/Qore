// Qore Engine written by Adam Weesner @ 2020
#include "Entity.h"


Entity::Entity(EntityContainer& newEntityContainer):
    entityContainer(newEntityContainer)
{
    isActive = true;
}

Entity::Entity(EntityContainer& newEntityContainer, std::string newName):
    entityContainer(newEntityContainer),
    name(newName)
{
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

std::string Entity::PrintComponents()
{
    std::string componentNames = "";

    for(Component* component : components)
    {
        componentNames += "\tComponent<" + component->name + ">\n";
    }

    return componentNames;
}