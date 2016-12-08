#include "Menu.hpp"

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "../Display.hpp"
#include "../Game.hpp"
#include "../media/Texture.hpp"
#include "../media/Sprite.hpp"
#include "../media/Text.hpp"

namespace State
{

    Menu::Menu(Game& game)
    : Game_State(game, TEXTURES_TOTAL, TEXTS_TOTAL)
    {
        loadMedia();
    }

    Menu::~Menu()
    {

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

        sTextures[TEXTURES_TEST]->render(0,0);
        sTexts[TEXTS_TEST]->render(20,20);

        SDL_RenderPresent( Display::getRenderer() );
    }

    void Menu::loadMedia()
    {
        sTextures[TEXTURES_TEST] = new Media::Texture();
        sTextures[TEXTURES_TEST]->load("ass/test.jpg");

        SDL_Color fontColor = {0,0,0};
        sTexts[TEXTS_TEST] = new Media::Text();
        sTexts[TEXTS_TEST]->load("TESTING", fontColor);

    }

}
