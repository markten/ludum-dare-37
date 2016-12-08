#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include "Media_Object.hpp"

namespace Media
{
    class Texture : public Media_Object
    {
        public:
            Texture();
            ~Texture();

            bool load(const std::string& fileName) override;
            void free();
            void render(int x, int y);
            int getWidth();
            int getHeight();

        private:
            SDL_Texture* texture = NULL;

            int width;
            int height;
    };
}

#endif // TEXTURE_HPP_INCLUDED
