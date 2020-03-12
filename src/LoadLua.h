// Qore Engine written by Adam Weesner @ 2020
#ifndef LOADLUA_H
#define LOADLUA_H

#include "../lib/lua/sol.hpp"
#include "EntityContainer.h"

extern EntityContainer entities;

class LoadLua
{
    public:
        LoadLua();
        void LoadLevel(int levelNum);
    
    private:
        void LoadAssets();
        void LoadMap();
        void LoadEntities();

        sol::state lua;
        sol::table levelData;
};

#endif