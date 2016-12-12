#ifndef SOUND_HPP_INCLUDED
#define SOUND_HPP_INCLUDED

#include "Media_Object.hpp"

#include <SDL2/SDL_mixer.h>

namespace Media
{
    class Sound : public Media_Object
    {
        public:
            Sound();
            ~Sound();

            bool load(const std::string& fileName) override;
            void free();
            void play(bool loop);

        private:
            Mix_Chunk* data = NULL;

    };
}

#endif // SOUND_HPP_INCLUDED
