// Qore Engine written by Adam Weesner @ 2020
#ifndef ENTITYCONTAINER_H
#define ENTITYCONTAINER_H

#include "Entity.h"
#include "Component.h"
#include <vector>

class EntityContainer
{    
    public:
        void ClearData();
        void Update(float deltaTime);
        void Render();
        void AddEntity(Entity* entity);
        std::vector<Entity*> GetEntities() const;
        unsigned int GetEntityCount();
        bool IsEmpty();
        std::string PrintEntities() const;
        std::vector<Entity*> GetEntitiesByLayer(Layers layer) const;

    private:
        std::vector<Entity*> entities;    
};

#endif
