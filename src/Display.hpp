#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include <SDL2/SDL.h>

namespace Display
{

    bool init();
    void close();

    void clear();
    void update();

    SDL_Surface* getSurface();
    SDL_Renderer* getRenderer();

    constexpr static int SCREEN_WIDTH = 800;
    constexpr static int SCREEN_HEIGHT = 600;

}

#endif // DISPLAY_HPP_INCLUDED
