// Qore Engine written by Adam Weesner @ 2020
#include "EntityContainer.h"

void EntityContainer::ClearData() 
{
    for (auto& entity: entities) 
    {
        entity->Destroy();
    }
}


void EntityContainer::Update(float deltaTime) 
{
    for (auto& entity: entities) 
    {
        entity->Update(deltaTime);
    }
}


void EntityContainer::Render() 
{
    for (auto& entity: entities) 
    {
        entity->Render();
    }
}


Entity& EntityContainer::AddEntity(std::string newEntityName) 
{
    Entity *entity = new Entity(*this, newEntityName);
    entities.emplace_back(entity);
    return *entity;
}


std::vector<Entity*> EntityContainer::GetEntities() const 
{
    return entities;
}


unsigned int EntityContainer::GetEntityCount() 
{
    return entities.size();
}


bool EntityContainer::IsEmpty() 
{
    return entities.size() == 0;
}


std::string EntityContainer::PrintEntities() 
{
    std::string entityNames = "";

    for(Entity* entity : entities)
    {
        entityNames += "Entity Name: " + entity->name + "\n"
                    + entity->PrintComponents();
    }
    return entityNames;
}