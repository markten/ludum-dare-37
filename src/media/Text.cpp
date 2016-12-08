#include "Text.hpp"

#include <iostream>

#include "../Display.hpp"

namespace Media
{
    bool Text::load(const std::string& textString, SDL_Color textColor)
    {
        free();

        text = std::string(textString);

        SDL_Surface* tempSurface = TTF_RenderText_Solid( Display::getFont(), textString.c_str(), textColor );
        if( tempSurface == NULL )
        {
            std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        }
        else
        {
            //Create texture from surface pixels
            texture = SDL_CreateTextureFromSurface( Display::getRenderer(), tempSurface );
            if( texture == NULL )
            {
                std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
            }
            else
            {
                //Get image dimensions
                width = tempSurface->w;
                height = tempSurface->h;
            }

            //Get rid of old surface
            SDL_FreeSurface( tempSurface );
        }

        //Return success
        return texture != NULL;
    }

    void Text::setColor(Uint8 r, Uint8 g, Uint8 b)
    {
        color = SDL_Color({r,g,b});
        load(text.c_str(), color);
    }

    void Text::setBlendMode(SDL_BlendMode blending)
    {

    }

    void Text::setAlpha(Uint8 alpha)
    {

    }

}
