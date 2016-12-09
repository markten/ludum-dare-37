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
    : Game_State(game, TEXTURE_TOTAL, SPRITE_TOTAL, TEXT_TOTAL)
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
                        sSprites[SPRITE_PLAYER]->setYVelocity(-5);
                    break;

                    case SDLK_DOWN:
                        sSprites[SPRITE_PLAYER]->setYVelocity(5);
                    break;

                    case SDLK_LEFT:
                        sSprites[SPRITE_PLAYER]->setXVelocity(-5);
                    break;

                    case SDLK_RIGHT:
                        sSprites[SPRITE_PLAYER]->setXVelocity(5);
                    break;

                    case SDLK_q:
                        p_game->quitGame();
                    break;

                    default:
                        // do nothing
                    break;
                }
            }
            else if( e.type == SDL_KEYUP )
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP:
                        sSprites[SPRITE_PLAYER]->setYVelocity(0);
                    break;

                    case SDLK_DOWN:
                        sSprites[SPRITE_PLAYER]->setYVelocity(0);
                    break;

                    case SDLK_LEFT:
                        sSprites[SPRITE_PLAYER]->setXVelocity(0);
                    break;

                    case SDLK_RIGHT:
                        sSprites[SPRITE_PLAYER]->setXVelocity(0);
                    break;

                    default:
                        // do nothing
                    break;
                }
            }
        }
    }

    void Menu::update()
    {
        sSprites[SPRITE_PLAYER]->update();
    }

    void Menu::draw()
    {
        sTextures[TEXTURE_TEST]->render(0, 0);
        sSprites[SPRITE_PLAYER]->render(sSprites[SPRITE_PLAYER]->getXPosition(), sSprites[SPRITE_PLAYER]->getYPosition());
        sTexts[TEXT_TEST]->render(Display::SCREEN_WIDTH/2-sTexts[TEXT_TEST]->getWidth()/2,Display::SCREEN_HEIGHT/2-sTexts[TEXT_TEST]->getHeight()/2);
    }

    void Menu::loadMedia()
    {
        // Load Background
        sTextures[TEXTURE_TEST] = new Media::Texture();
        sTextures[TEXTURE_TEST]->load("ass/mountain.jpg");

        // Load Player Sprite
        std::cout << "Loaded Player Sprite" << std::endl;
        sSprites[SPRITE_PLAYER] = new Media::Sprite(0, 0);
        sSprites[SPRITE_PLAYER]->load("ass/spurdo.png");

        // Load Text
        SDL_Color fontColor = {255,0,0};
        sTexts[TEXT_TEST] = new Media::Text();
        sTexts[TEXT_TEST]->load("TESTING", fontColor);
    }

}
