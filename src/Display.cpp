#include "Display.hpp"

#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "GTimer.hpp"

class GTimer;

namespace Display
{
    // Pointers to SDL components
    SDL_Window* window;
    SDL_Surface* sWindowSurface;
    SDL_Renderer* renderer;
    TTF_Font* DejaVuSansMono;
    TTF_Font* Bungee;
    TTF_Font* BungeeOutline;

    // FPS counter setup
    GTimer fpsTimer;
    GTimer capTimer;
    std::stringstream fpsString;
    uint32_t frameCount = 0;

    bool init()
    {
        bool success = true;

        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        {
            std::cout << "SDL could not initialize! SDL_error: %s\n" << SDL_GetError() << std::endl;
            success = false;
        }

        else
        {
            window = SDL_CreateWindow("Ludum Dare 37 - Robovac Simulator 2016",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         SCREEN_WIDTH, SCREEN_HEIGHT,
                         SDL_WINDOW_SHOWN);
                         // | SDL_WINDOW_FULLSCREEN

            if(window == NULL)
            {
                std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                //| SDL_RENDERER_PRESENTVSYNC

                if(renderer == NULL)
                {
                    std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                    success = false;
                }
                else
                {
                    int imgFlags = IMG_INIT_PNG;
                    if(!(IMG_Init(imgFlags) & imgFlags))
                    {
                        std::cout << "SDL_image could not instantialize! SDL_image Error: " << IMG_GetError() << std::endl;
                        success = false;
                    }

                    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                    {
                        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
                        success = false;
                    }

                    if( TTF_Init() == -1 )
                    {
                        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
                        success = false;
                    }
                    else
                    {
                        DejaVuSansMono = TTF_OpenFont( "ass/DejaVuSansMono.ttf", 28 );
                        if( DejaVuSansMono == NULL )
                        {
                            std::cout << "Failed to load DejaVuSansMono.ttf! SDL_ttf Error: " << TTF_GetError() << std::endl;
                            success = false;
                        }
                    }

                    SDL_SetRenderDrawColor( Display::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
                    sWindowSurface = SDL_GetWindowSurface(window);
                    fpsTimer.start();
                    capTimer.start();
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
        Mix_Quit();
        SDL_Quit();
    }

    void update()
    {
        int frameTicks = capTimer.getTicks();
        if( frameTicks < SCREEN_TICKS_PER_FRAME )
        {
            //Wait remaining time
            SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
        }

        // Render and clear the window
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        ++frameCount;

        // update FPS average
        float avgFPS = frameCount / ( fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 )
        {
            avgFPS = 0;
        }

        std::cout << "AVG FPS: " << avgFPS << std::endl;
        capTimer.start();
    }

    SDL_Window* getWindow()
    {
        return window;
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
