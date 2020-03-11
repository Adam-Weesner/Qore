// Qore Engine written by Adam Weesner @ 2020
#include "Entity.h"
#include <string>

extern EntityContainer entities;

Entity::Entity():
    entityContainer(entities)
{
    entityContainer.AddEntity(this);
    isActive = true;
}

Entity::Entity(std::string name, Layers layer):
    entityContainer(entities),
    name(name),
    layer(layer)
{
    entityContainer.AddEntity(this);
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
    for (int i = 0; i < entities.GetEntities().size(); i++)
    {
        if (entities.GetEntities()[i] == this)
        {
            entities.GetEntities().erase(entities.GetEntities().begin() + i);
            break;
        }
    }
}


bool Entity::IsActive() const
{
    return isActive;
}

std::string Entity::PrintComponents()
{
    std::string componentNames = "";

    for(auto component : componentTMap)
    {
        std::string compName(component.first->name());
        componentNames += "\tComponent<" + compName + ">\n";
    }

    return componentNames;
}