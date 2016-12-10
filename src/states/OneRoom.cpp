#include "OneRoom.hpp"

#include <iostream>

#include <SDL2/SDL.h>
#include <array>

#include "../Game.hpp"
#include "Menu.hpp"
#include "../maps/RoomOne.hpp"

namespace State
{
    OneRoom::OneRoom(Game& game)
    : Game_State(game, TEXTURE_TOTAL, SPRITE_TOTAL, TEXT_TOTAL, SOUND_TOTAL, MUSIC_TOTAL)
    {
        loadMedia();
        loadMap();
        std::cout << "GAME STATE: OneRoom" << std::endl;
    }

    OneRoom::~OneRoom()
    {

    }

    void OneRoom::input()
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
                        //sSprites[SPRITE_PLAYER]->setYVelocity(-5);
                    break;

                    case SDLK_DOWN:
                        //sSprites[SPRITE_PLAYER]->setYVelocity(5);
                    break;

                    case SDLK_LEFT:
                        //sSprites[SPRITE_PLAYER]->setXVelocity(-5);
                    break;

                    case SDLK_RIGHT:
                        //sSprites[SPRITE_PLAYER]->setXVelocity(5);
                    break;

                    case SDLK_q:
                        p_game->quitGame();
                    break;

                    case SDLK_m:
                        printMap();
                    break;

                    case SDLK_RETURN:
                        p_game->popState();
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
                        //sSprites[SPRITE_PLAYER]->setYVelocity(0);
                    break;

                    case SDLK_DOWN:
                        //sSprites[SPRITE_PLAYER]->setYVelocity(0);
                    break;

                    case SDLK_LEFT:
                        //sSprites[SPRITE_PLAYER]->setXVelocity(0);
                    break;

                    case SDLK_RIGHT:
                        //sSprites[SPRITE_PLAYER]->setXVelocity(0);
                    break;

                    default:
                        // do nothing
                    break;
                }
            }
        }
    }

    void OneRoom::update()
    {

    }

    void OneRoom::draw()
    {
        // render floor
        sTextures[TEXTURE_FLOOR]->render(0,0);

        //render robot

        // render furniture

        // render text/score
    }

    void OneRoom::loadMedia()
    {
        std::cout << "Loading textures..." << std::endl;
        sTextures[TEXTURE_FLOOR] = new Media::Texture();
        sTextures[TEXTURE_FLOOR]->load("ass/floor.png");
        std::cout << "\tdone." << std::endl;
    }

    void OneRoom::loadMap()
    {
        currentMap = Map::MAP_ROOM_ONE;
    }

    void OneRoom::printMap()
    {
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 20; j++)
            {
                std::cout << currentMap[i][j] << ", ";
            }
            std::cout << std::endl;
        }
    }


}
