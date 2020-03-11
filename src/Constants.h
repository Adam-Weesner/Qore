// Qore Engine written by Adam Weesner @ 2020
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

const float DELTA_MAX = 0.05f;

enum Layers
{
    TILEMAP_LAYER,
    ENVIRONMENT_LAYER,
    ENEMY_LAYER,
    PLAYER_LAYER,
    PROJECTILE_LAYER,
    UI_LAYER
};

const unsigned int NUM_LAYERS = 6;

const SDL_Color WHITE_COLOR = {255, 255, 255, 255};
const SDL_Color RED_COLOR = {255, 0, 0, 255};
const SDL_Color GREEN_COLOR = {0, 255, 0, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255, 255};

#endif