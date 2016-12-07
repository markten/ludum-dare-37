#include "Menu.hpp"

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "../Display.hpp"
#include "../media/Image.hpp"

enum ImageSurfaces
{
    TEST_IMAGE,
    IMAGE_SURFACES_TOTAL
};

namespace State
{

    Menu::Menu(Game& game)
    : Game_State(game)
    , imageSurfaces{new Media::Image*[IMAGE_SURFACES_TOTAL]}
    {
        imageSurfaces[TEST_IMAGE] = new Media::Image();
        imageSurfaces[TEST_IMAGE]->load("test.bmp");
    }

    void Menu::input()
    {

    }

    void Menu::update()
    {

    }

    void Menu::draw()
    {
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = Display::SCREEN_WIDTH;
        stretchRect.h = Display::SCREEN_HEIGHT;
        SDL_BlitScaled( imageSurfaces[TEST_IMAGE]->surface, NULL, Display::getSurface(), &stretchRect );
        //SDL_BlitSurface( imageSurfaces[TEST_IMAGE]->surface, NULL, Display::getSurface(), NULL );
        //std::cout << "Drawing!" << std::endl;

    }

}
