#include "Music.hpp"

#include <iostream>
#include <SDL2/SDL_mixer.h>

namespace Media
{
    Music::Music()
    {

    }

    Music::~Music()
    {
        free();
    }

    bool Music::load(const std::string& fileName)
    {
        bool success = true;

        free();

        data = Mix_LoadMUS(fileName.c_str());
        if( data == NULL )
        {
            std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
            success = false;
        }

        return success;
    }

    void Music::play()
    {
        if(!isPlaying())
        {
            Mix_PlayMusic( data, -1 );
        }
    }

    void Music::pause()
    {
        Mix_PauseMusic();
    }

    void Music::resume()
    {
        Mix_ResumeMusic();
    }

    void Music::stop()
    {
        Mix_HaltMusic();
    }

    bool Music::isPlaying()
    {
        return Mix_PlayingMusic();
    }

    void Music::free()
    {
        Mix_FreeMusic(data);
        data = NULL;
    }

}
