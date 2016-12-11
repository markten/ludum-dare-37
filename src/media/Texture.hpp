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
            void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
            void setAlpha(uint8_t alpha);
            int getWidth();
            int getHeight();

        protected:
            SDL_Texture* texture = NULL;

            int width;
            int height;
    };
}

#endif // TEXTURE_HPP_INCLUDED
