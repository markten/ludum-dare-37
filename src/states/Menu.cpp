#include "Menu.hpp"

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "../Display.hpp"
#include "../Game.hpp"
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
        frameCount++;
        sSprites[SPRITE_PLAYER]->update();
        if(frameCount == 60)
        {
            displayText = !displayText;
            frameCount = 0;
        }

        // update FPS display
        //SDL_Color fontColor = {255,0,0};
        //sTexts[TEXT_FPS]->load(Display::getFPSString(), fontColor);
    }

    void Menu::draw()
    {
        sTextures[TEXTURE_BACKGROUND]->render(0, 0);
        //sSprites[SPRITE_PLAYER]->render(sSprites[SPRITE_PLAYER]->getXPosition(), sSprites[SPRITE_PLAYER]->getYPosition());
        if(displayText) sTexts[TEXT_ENTER]->render(Display::SCREEN_WIDTH/2-sTexts[TEXT_ENTER]->getWidth()/2, 500-sTexts[TEXT_ENTER]->getHeight()/2);
        //sTexts[TEXT_FPS]->render(0, 0);
    }

    void Menu::loadMedia()
    {
        // Load Background
        std::cout << "Loading textures..." << std::endl;
        sTextures[TEXTURE_BACKGROUND] = new Media::Texture();
        sTextures[TEXTURE_BACKGROUND]->load("ass/title_background.png");
        std::cout << "\tdone." << std::endl;

        // Load Player Sprite
        std::cout << "Loading sprites..." << std::endl;
        sSprites[SPRITE_PLAYER] = new Media::Sprite(0, 0);
        sSprites[SPRITE_PLAYER]->load("ass/spurdo.png");
        std::cout << "\tdone." << std::endl;

        // Load Text
        std::cout << "Loading fonts..." << std::endl;
        SDL_Color fontColor = {255,0,0};
        sTexts[TEXT_ENTER] = new Media::Text();
        sTexts[TEXT_ENTER]->load("Press Enter...", fontColor);
        //sTexts[TEXT_FPS] = new Media::Text();
        //sTexts[TEXT_FPS]->load("FPS: 0", fontColor);
        std::cout << "\tdone." << std::endl;

        // Load Sounds
        std::cout << "Loading sounds..." << std::endl;
        sSounds[SOUND_TEST] = new Media::Sound();
        sSounds[SOUND_TEST]->load("ass/test.ogg");
        std::cout << "\tdone." << std::endl;
    }

}
