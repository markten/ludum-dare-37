#include "Sound.hpp"

#include <iostream>
#include <SDL2/SDL_mixer.h>

namespace Media
{
    Sound::Sound()
    {

    }

    Sound::~Sound()
    {
        free();
    }

    bool Sound::load(const std::string& fileName)
    {
        bool success = true;

        free();

        data = Mix_LoadWAV(fileName.c_str());
        if(data == NULL)
        {
            std::cout << "Failed to load " << fileName << " sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
            success = false;
        }

        return success;
    }

    void Sound::free()
    {
        Mix_FreeChunk(data);
        data = NULL;
    }

    void Sound::play(bool loop)
    {
        if(loop)
        {
            Mix_PlayChannel(-1, data, -1);
        }
        else
        {
            Mix_PlayChannel(-1, data, 0);
        }

    }

}
