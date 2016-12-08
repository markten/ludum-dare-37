#include "Menu.hpp"

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "../Display.hpp"
#include "../media/Image.hpp"
#include "../Game.hpp"

enum ImageSurfaces
{
    TEST_IMAGE,
    IMAGE_SURFACES_TOTAL
};

namespace State
{

    Menu::Menu(Game& game)
    : Game_State(game)
    , imageSurfaces{new Media::Texture*[IMAGE_SURFACES_TOTAL]}
    {
        imageSurfaces[TEST_IMAGE] = new Media::Texture();
        imageSurfaces[TEST_IMAGE]->load("test.jpg");
    }

    void Menu::input()
    {
        SDL_Event e;

        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                p_game->quitGame();
            }
            //User presses a key
            else if( e.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP:
                    //gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                    break;

                    case SDLK_DOWN:
                    //gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                    break;

                    case SDLK_LEFT:
                    //gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                    break;

                    case SDLK_RIGHT:
                    //gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                    break;

                    case SDLK_q:
                        p_game->quitGame();
                    break;

                    default:
                    //gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                    break;
                }
            }
        }
    }

    void Menu::update()
    {

    }

    void Menu::draw()
    {
        SDL_RenderClear( Display::getRenderer() );
        imageSurfaces[TEST_IMAGE]->render(0,0);
        SDL_RenderPresent( Display::getRenderer() );
        /*SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = Display::SCREEN_WIDTH;
        stretchRect.h = Display::SCREEN_HEIGHT;
        SDL_BlitScaled( imageSurfaces[TEST_IMAGE]->surface, NULL, Display::getSurface(), &stretchRect );
        */
        //SDL_BlitSurface( imageSurfaces[TEST_IMAGE]->surface, NULL, Display::getSurface(), NULL );
        //std::cout << "Drawing!" << std::endl;

    }

}
