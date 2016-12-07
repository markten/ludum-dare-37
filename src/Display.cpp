#include "Display.hpp"

#include <iostream>
#include <SDL2/SDL.h>

namespace Display
{
    SDL_Window* window;
    SDL_Surface* sWindowSurface;

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
                         SDL_WINDOW_SHOWN );

            if(window == NULL)
            {
                std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                sWindowSurface = SDL_GetWindowSurface(window);
            }
        }


        return success;
    }

    void close()
    {
        SDL_FreeSurface(sWindowSurface);
        sWindowSurface = NULL;

        SDL_DestroyWindow(window);
        window = NULL;

        SDL_Quit();
    }

    void update()
    {
        SDL_UpdateWindowSurface(window);
    }

    bool isOpen()
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                return false;
            }
        }

        return true;
    }

    SDL_Surface* getSurface()
    {
        return sWindowSurface;
    }

}
