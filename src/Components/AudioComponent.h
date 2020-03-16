// Qore Engine written by Adam Weesner @ 2020
#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H

#include <SDL2/SDL_mixer.h>
#include "../AssetHandler.h"

class AudioComponent: public Component
{
    public:
        AudioComponent(std::string filePath, bool playOnAwake, bool isLooping)
        {
            this->isLooping = isLooping;

            //Initialize SDL
            if (SDL_Init(SDL_INIT_AUDIO) < 0)
            {
                std::cout << "ERROR - SDL could not initialize." << std::endl;
                return;
            }

            //Initialize SDL_mixer
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                std::cout << "ERROR - SDL_mixer could not initialize." << std::endl;
                return;
            }

            sound = Mix_LoadWAV(filePath.c_str());

            if (sound == NULL)
            {
                std::cout << "ERROR - Failed to load sound." << std::endl;
                return;
            }

            if (playOnAwake)
            {
                Play();
            }
        }


        void Play(int timesLooping = 0)
        {
            if (isLooping)
            {
                timesLooping = -1;
            }

            Mix_PlayChannel(-1, sound, timesLooping);
        }


        void Close()
        {
            Mix_FreeChunk(sound);
            sound = NULL;
            Mix_Quit();
        }


    private:
        Mix_Chunk *sound = NULL;
        bool isLooping;
};

#endif