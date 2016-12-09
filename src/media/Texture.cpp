#include "Texture.hpp"

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Display.hpp"

namespace Media
{
    Texture::Texture()
    {

    }

    Texture::~Texture()
    {
        free();
    }

    bool Texture::load(const std::string& fileName)
    {
        free();

        SDL_Surface* tempSurface = IMG_Load( fileName.c_str() );
        if( tempSurface == NULL )
        {
            std::cout << "Unable to load image " << fileName << "! SDL_image Error: " << IMG_GetError() << std::endl;
        }
        else
        {
            SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0));
            texture = SDL_CreateTextureFromSurface( Display::getRenderer(), tempSurface );
            if( texture == NULL )
            {
                std::cout << "Unable to create texture from " << fileName << "! SDL Error: " << SDL_GetError() << std::endl;
            }
            else
            {
                width = tempSurface->w;
                height = tempSurface->h;
            }

            SDL_FreeSurface( tempSurface );
        }

        return (texture != NULL);
    }

    void Texture::free()
    {
        if(texture != NULL)
        {
            SDL_DestroyTexture(texture);
            texture = NULL;
            width = 0;
            height = 0;
        }

    }

    void Texture::render(int x, int y)
    {
        SDL_Rect renderrect = {x, y, width, height};
        SDL_RenderCopy(Display::getRenderer(), texture, NULL, &renderrect);
    }

    int Texture::getWidth()
    {
        return width;
    }

    int Texture::getHeight()
    {
        return height;
    }

}
