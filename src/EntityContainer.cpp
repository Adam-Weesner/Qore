// Qore Engine written by Adam Weesner @ 2020
#include "EntityContainer.h"

void EntityContainer::ClearData()
{
    for(auto& entity : entities)
    {
        entity->Destroy();
    }
}


void EntityContainer::Update(float deltaTime)
{
    for(auto& entity : entities)
    {
        entity->Update(deltaTime);
    }
}


void EntityContainer::Render()
{
    for(auto& entity : entities)
    {
        entity->Render();
    }
}


Entity& EntityContainer::AddEntity(std::string entityName)
{
    Entity* newEntity = new Entity(*this, entityName);
    entities.emplace_back(newEntity);
}


std::vector<Entity*> EntityContainer::GetEntities() const
{
    return entities;
}


unsigned int EntityContainer::GetEntityCount() const
{
    return entities.size();
}


bool EntityContainer::ContainsEntities()
{
    return entities.size() > 0;
}