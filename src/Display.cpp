#include "Display.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace Display
{
    SDL_Window* window;
    SDL_Surface* sWindowSurface;
    SDL_Renderer* renderer;
    TTF_Font* DejaVuSansMono;

    SDL_Event e;

    bool init()
    {
        bool success = true;

        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "SDL could not initialize! SDL_error: %s\n" << SDL_GetError() << std::endl;
            success = false;
        }

        else
        {
            window = SDL_CreateWindow("Ludum Dare 37",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         SCREEN_WIDTH, SCREEN_HEIGHT,
                         SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

            if(window == NULL)
            {
                std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                if(renderer == NULL)
                {
                    std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                    success = false;
                }
                else
                {

                    SDL_SetRenderDrawColor( Display::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );

                    int imgFlags = IMG_INIT_PNG;
                    if(!(IMG_Init(imgFlags) & imgFlags))
                    {
                        std::cout << "SDL_image could not instantialize! SDL_image Error: " << IMG_GetError() << std::endl;
                        success = false;
                    }

                    if( TTF_Init() == -1 )
                    {
                        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
                        success = false;
                    }

                    DejaVuSansMono = TTF_OpenFont( "ass/DejaVuSansMono.ttf", 28 );
                    if( DejaVuSansMono == NULL )
                    {
                        std::cout << "Failed to load DejaVuSansMono.ttf! SDL_ttf Error: " << TTF_GetError() << std::endl;
                        success = false;
                    }

                    else
                    {
                        sWindowSurface = SDL_GetWindowSurface(window);
                    }
                }
            }

        }


        return success;
    }

    void close()
    {
        TTF_CloseFont(DejaVuSansMono);
        DejaVuSansMono = NULL;

        SDL_FreeSurface(sWindowSurface);
        sWindowSurface = NULL;

        SDL_DestroyRenderer(renderer);
        renderer = NULL;

        SDL_DestroyWindow(window);
        window = NULL;

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void update()
    {
        SDL_UpdateWindowSurface(window);
    }

    SDL_Surface* getSurface()
    {
        return sWindowSurface;
    }

    SDL_Renderer* getRenderer()
    {
        return renderer;
    }

    TTF_Font* getFont()
    {
        return DejaVuSansMono;
    }

}
