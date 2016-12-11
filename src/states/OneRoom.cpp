#include "OneRoom.hpp"

#include <iostream>

#include <SDL2/SDL.h>
#include <array>

#include "../Display.hpp"
#include "../Game.hpp"
#include "Menu.hpp"
#include "../maps/RoomOne.hpp"
#include "../Player.hpp"

namespace State
{
    int GRID = 40;

    OneRoom::OneRoom(Game& game)
    : Game_State(game, TEXTURE_TOTAL, SPRITE_TOTAL, TEXT_TOTAL, SOUND_TOTAL, MUSIC_TOTAL)
    {
        loadMedia();
        loadMap();
        //sMusic[MUSIC_CLAVIER]->play();
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
                        sPlayer->setGoingForward(true);
                    break;

                    case SDLK_DOWN:
                        sPlayer->setGoingBackward(true);
                    break;

                    case SDLK_LEFT:
                        sPlayer->setTurningLeft(true);
                        std::cout << "Turning left." <<std::endl;
                    break;

                    case SDLK_RIGHT:
                        sPlayer->setTurningRight(true);
                        std::cout << "Turning right." <<std::endl;
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
                        sPlayer->setGoingForward(false);
                    break;

                    case SDLK_DOWN:
                        sPlayer->setGoingBackward(false);
                    break;

                    case SDLK_LEFT:
                        sPlayer->setTurningLeft(false);
                    break;

                    case SDLK_RIGHT:
                        sPlayer->setTurningRight(false);
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
        // Check robot position
        // set player-occupied grid sector to clean
            int xIndex = sPlayer->getXPosition() / GRID;
            int yIndex = sPlayer->getYPosition() / GRID;
            if(currentMap[yIndex][xIndex] == Map::DIRTY)
            {
                currentMap[yIndex][xIndex] = Map::CLEAN;
            }


            // MAYBE: set robot velocity based on flooring type
        // Check grid for cleanliness
        if(mapIsClean())
        {
            // push victory game state
            // set victory variable pop back up to menu
        }
        // update bot position
        //sSprites[SPRITE_PLAYER]->update(currentMap);
            sPlayer->update();
            // check for collisions
            if(sPlayer->getXPosition() < 0) sPlayer->setXPosition(0);
            if(sPlayer->getYPosition() < 0) sPlayer->setYPosition(0);
            if(sPlayer->getXPosition() > Display::SCREEN_WIDTH-sPlayer->getWidth()) sPlayer->setXPosition(Display::SCREEN_WIDTH-sPlayer->getWidth());
            if(sPlayer->getYPosition() > Display::SCREEN_HEIGHT-sPlayer->getHeight()) sPlayer->setYPosition(Display::SCREEN_HEIGHT-sPlayer->getHeight());

    }

    void OneRoom::draw()
    {
        // render floor
        for(int row = 0; row < 15; row++)
        {
            for(int col = 0; col < 20; col++)
            {
                switch(currentMap[row][col])
                {
                    case Map::DIRTY:
                        sTextures[TEXTURE_CLEANFLOOR]->render(GRID*col,GRID*row);
                        sTextures[TEXTURE_DIRTYFLOOR]->render(GRID*col,GRID*row,NULL,currentMapRotations[row][col]);
                        break;
                    case Map::CLEAN:
                        sTextures[TEXTURE_CLEANFLOOR]->render(GRID*col,GRID*row);
                        break;
                    case Map::BASE:
                        sTextures[TEXTURE_CLEANFLOOR]->render(GRID*col,GRID*row);
                        sTextures[TEXTURE_BASE]->render(GRID*col,GRID*row);
                        break;
                    default:
                        sTextures[TEXTURE_CLEANFLOOR]->render(GRID*col,GRID*row);
                    break;
                }
            }
        }

        //render robot
        std::cout << "Player direction: " << sPlayer->getDirection() <<std::endl;
        sPlayer->render(sPlayer->getXPosition(), sPlayer->getYPosition(), NULL, -sPlayer->getDirection());
        // render furniture

        // render text/score
    }

    void OneRoom::loadMedia()
    {
        std::cout << "Loading textures..." << std::endl;

        sTextures[TEXTURE_CLEANFLOOR] = new Media::Texture();
        sTextures[TEXTURE_CLEANFLOOR]->load("ass/floor_clean.png");

        sTextures[TEXTURE_DIRTYFLOOR] = new Media::Texture();
        sTextures[TEXTURE_DIRTYFLOOR]->load("ass/floor_dirty.png");
        sTextures[TEXTURE_DIRTYFLOOR]->setAlpha(100);

        sTextures[TEXTURE_BASE] = new Media::Texture();
        sTextures[TEXTURE_BASE]->load("ass/base.png");

        std::cout << "\tdone." << std::endl;

        std::cout << "Loading sprites..." << std::endl;

        sPlayer = new Media::Player();
        sPlayer->load("ass/robot.png");

        std::cout << "\tdone." << std::endl;

        std::cout << "Loading music..." << std::endl;

        sMusic[MUSIC_CLAVIER] = new Media::Music();
        sMusic[MUSIC_CLAVIER]->load("ass/well-tempered-clavier.ogg");

        std::cout << "\tdone." << std::endl;

    }

    void OneRoom::loadMap()
    {
        currentMap = Map::MAP_ROOM_ONE;

        int rotationAngles[] = {0, 90, 180, 720};

        for(int row = 0; row < 15; row++)
        {
            for(int col = 0; col < 20; col++)
            {
                currentMapRotations[row][col] = rotationAngles[rand()%4];
            }
        }

    }

    void OneRoom::printMap()
    {
        for(int row = 0; row < 15; row++)
        {
            for(int col = 0; col < 20; col++)
            {
                std::cout << currentMap[row][col] << ", ";
            }
            std::cout << std::endl;
        }
    }

    bool OneRoom::mapIsClean()
    {
        for(int row = 0; row < 15; row++)
        {
            for(int col = 0; col < 20; col++)
            {
                if(currentMap[row][col] == Map::DIRTY) return false;
            }
        }

        return true;
    }


}
