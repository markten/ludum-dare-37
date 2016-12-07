#include "Image.hpp"

#include <string>
#include <iostream>

#include <SDL2/SDL.h>

#include "../Display.hpp"

namespace Media
{
    Image::Image()
    {

    }

    Image::~Image()
    {
        SDL_FreeSurface(surface);
        surface = NULL;
    }

    bool Image::load(const std::string& fileName)
    {
        bool success = true;

        SDL_Surface* tempSurface = SDL_LoadBMP(fileName.c_str());
        if(tempSurface == NULL)
        {
            std::cout << "Unable to load image " << fileName << " SDL Error: " << SDL_GetError() <<std::endl;
            success = false;
        }
        else
        {
            surface = SDL_ConvertSurface(tempSurface, Display::getSurface()->format, 0);
            if( surface == NULL )
            {
                std::cout << "Unable to optimize image " << fileName << "! SDL Error: " << SDL_GetError() << std::endl;
            }
            SDL_FreeSurface(tempSurface);
        }
        return success;
    }
}
