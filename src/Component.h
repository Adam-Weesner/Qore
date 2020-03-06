// QORE Engine written by Adam Weesner @ 2020
#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
    public:
        virtual ~Component() {}
        virtual void Update(float deltaTime) {}
        virtual void Render() {}

        Entity* owner;
};
#endif