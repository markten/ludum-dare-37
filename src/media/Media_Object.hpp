#ifndef MEDIA_HPP_INCLUDED
#define MEDIA_HPP_INCLUDED

#include <string>

#include <SDL2/SDL.h>

namespace Media
{
    class Media_Object
    {
        public:
            Media_Object();

            virtual bool load(const std::string& fileName) = 0;
            SDL_Surface* surface = NULL;
    };


}

#endif // MEDIA_HPP_INCLUDED
