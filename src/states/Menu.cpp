#include "Menu.hpp"

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "../Display.hpp"
#include "../Game.hpp"
#include "Game_State.hpp"
#include "Scores.hpp"
#include "OneRoom.hpp"
#include "../media/Texture.hpp"
#include "../media/Sprite.hpp"
#include "../media/Text.hpp"

namespace State
{

    Menu::Menu(Game& game)
    : Game_State(game, TEXTURE_TOTAL, SPRITE_TOTAL, TEXT_TOTAL, SOUND_TOTAL, MUSIC_TOTAL)
    {
        loadMedia();
        std::cout << "GAME STATE: Menu" << std::endl;
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
                    case SDLK_q:
                        p_game->quitGame();
                    break;

                    case SDLK_f:
                        if(SDL_GetWindowFlags(Display::getWindow()) & SDL_WINDOW_FULLSCREEN)
                        {
                            SDL_SetWindowFullscreen(Display::getWindow(), 0);
                        }
                        else
                        {
                            SDL_SetWindowFullscreen(Display::getWindow(), SDL_WINDOW_FULLSCREEN);
                        }
                    break;

                    case SDLK_h:
                        displayHelp = !displayHelp;
                    break;

                    case SDLK_s:
                        p_game->pushState(std::make_unique<State::Scores>(*p_game));
                    break;

                    case SDLK_RETURN:
                        p_game->pushState(std::make_unique<State::OneRoom>(*p_game));
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
        // if player has one, push the high score screen state
        if(p_game->getPlayerWon())
        {
            p_game->setPlayerWon(false);
            p_game->pushState(std::make_unique<State::Scores>(*p_game));
        }

        // one second counter to have blinking text
        frameCount++;
        if(frameCount == 60)
        {
            displayText = !displayText;
            frameCount = 0;
        }
    }

    void Menu::draw()
    {
        sTextures[TEXTURE_BACKGROUND]->render(0, 0);
        if(displayText) sTexts[TEXT_ENTER]->render(Display::SCREEN_WIDTH/2-sTexts[TEXT_ENTER]->getWidth()/2, 400);
        sTexts[TEXT_HELP]->render(10, 560);
        if(displayHelp) sTextures[TEXTURE_HELP]->render(50,50);
    }

    void Menu::loadMedia()
    {
        // Load Background
        std::cout << "Loading textures..." << std::endl;

        sTextures[TEXTURE_BACKGROUND] = new Media::Texture();
        sTextures[TEXTURE_BACKGROUND]->load("ass/title_background.png");

        sTextures[TEXTURE_HELP] = new Media::Texture();
        sTextures[TEXTURE_HELP]->load("ass/helpscreen.png");

        std::cout << "\tdone." << std::endl;

        // Load Text
        std::cout << "Loading fonts..." << std::endl;

        SDL_Color fontColor = {255,0,0,255};
        sTexts[TEXT_ENTER] = new Media::Text();
        sTexts[TEXT_ENTER]->load("Press Enter...", fontColor);

        fontColor = {0,0,0,255};
        sTexts[TEXT_HELP] = new Media::Text();
        sTexts[TEXT_HELP]->load("Press \"h\" to toggle help", fontColor);

        std::cout << "\tdone." << std::endl;

    }

}
