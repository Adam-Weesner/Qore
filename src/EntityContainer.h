// Qore Engine written by Adam Weesner @ 2020
#ifndef EntityContainer_H
#define EntityContainer_H

#include "Entity.h"
#include "Component.h"
#include <vector>
#include <string>

class EntityContainer
{
    public:
        void ClearData();
        void Update(float deltaTime);
        void Render();
        Entity& AddEntity(std::string entityName);
        std::vector<Entity*> GetEntities() const;
        unsigned int GetEntityCount() const;
        bool ContainsEntities();

    private:
        std::vector<Entity*> entities;
};

#endif