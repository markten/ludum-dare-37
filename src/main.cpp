#include "Display.hpp"
#include "Game.hpp"

#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
    if(Display::init())
    {
        Game game;
        game.runMainGameLoop();
    }
    else
    {
        Display::close();
    }

    return 0;
}
