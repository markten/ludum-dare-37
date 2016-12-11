#ifndef TEXT_HPP_INCLUDED
#define TEXT_HPP_INCLUDED

#include <SDL2/SDL.h>

#include "Texture.hpp"

namespace Media
{

    class Text : public Texture
    {
        public:

            bool load(const std::string& textString,
                      SDL_Color textColor
                      );

            void setColor(Uint8 r,
                          Uint8 g,
                          Uint8 b);

            void setBlendMode(SDL_BlendMode blending);

            void setAlpha(Uint8 alpha);

        private:
            SDL_Color color = {0, 0, 0};
            std::string text;

    };

}

#endif // TEXT_HPP_INCLUDED
