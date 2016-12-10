#ifndef MUSIC_HPP_INCLUDED
#define MUSIC_HPP_INCLUDED

#include "Media_Object.hpp"

#include <SDL2/SDL_mixer.h>

namespace Media
{
    class Music : public Media_Object
    {
        public:
            Music();
            ~Music();

            bool load(const std::string& fileName) override;
            void play();
            void pause();
            void resume();
            void stop();
            bool isPlaying();
            void free();

        private:
            Mix_Music* data = NULL;

    };
}

#endif // MUSIC_HPP_INCLUDED
