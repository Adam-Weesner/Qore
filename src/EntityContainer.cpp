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
    for (int layerNum = 0; layerNum < NUM_LAYERS; layerNum++)
    {
        for (auto& entity : GetEntitiesByLayer(static_cast<Layers>(layerNum)))
        {
            entity->Render();
        }
    }
}


Entity& EntityContainer::AddEntity(std::string newEntityName, Layers layer) 
{
    Entity *entity = new Entity(*this, newEntityName, layer);
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


std::string EntityContainer::PrintEntities() const
{
    std::string entityNames = "";

    for(Entity* entity : entities)
    {
        entityNames += "Entity Name: " + entity->name + "\n"
                    + entity->PrintComponents();
    }
    return entityNames;
}


std::vector<Entity*> EntityContainer::GetEntitiesByLayer(Layers layer) const
{
    std::vector<Entity*> selectedEntities;

    for (auto& entity : entities)
    {
        if (entity->layer == layer)
        {
            selectedEntities.emplace_back(entity);
        }
    }

    return selectedEntities;
}