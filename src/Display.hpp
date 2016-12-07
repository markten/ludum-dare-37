#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include <SDL2/SDL.h>

namespace Display
{

    bool init();
    void close();

    void clear();
    void update();

    bool isOpen();

    SDL_Surface* getSurface();

    constexpr static int SCREEN_WIDTH = 800;
    constexpr static int SCREEN_HEIGHT = 600;

}

#endif // DISPLAY_HPP_INCLUDED
