#include "OneRoom.hpp"

#include <SDL2/SDL.h>
#include <array>
#include <time.h>
#include <iostream>
#include <memory>

#include "../Display.hpp"
#include "../Game.hpp"
#include "Menu.hpp"
#include "../maps/RoomOne.hpp"
#include "../Player.hpp"
#include "../GTimer.hpp"

namespace State
{
    OneRoom::OneRoom(Game& game)
    : Game_State(game, TEXTURE_TOTAL, SPRITE_TOTAL, TEXT_TOTAL, SOUND_TOTAL, MUSIC_TOTAL)
    {
        loadMedia();
        loadMap();

        gameTimer.start();
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
                    break;

                    case SDLK_RIGHT:
                        sPlayer->setTurningRight(true);
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
        // MAYBE: set robot velocity based on flooring type
        // update bot position
        sPlayer->update();

        // get player position in terms of grid coordinates
        int currentCol = (sPlayer->getXPosition() + sPlayer->getWidth()/2) / Map::GRID;
        int currentRow = (sPlayer->getYPosition() + sPlayer->getHeight()/2) / Map::GRID;

        // check for wall collisions
        if(sPlayer->getXPosition() < 0) sPlayer->setXPosition(0);
        if(sPlayer->getYPosition() < 0) sPlayer->setYPosition(0);
        if(sPlayer->getXPosition() > Display::SCREEN_WIDTH-sPlayer->getWidth()) sPlayer->setXPosition(Display::SCREEN_WIDTH-sPlayer->getWidth());
        if(sPlayer->getYPosition() > Display::SCREEN_HEIGHT-sPlayer->getHeight()) sPlayer->setYPosition(Display::SCREEN_HEIGHT-sPlayer->getHeight());

        // check for furniture collisions
        if(currentMap[currentRow][currentCol] == Map::OCCUPIED)
        {
            sPlayer->moveBack();
        }

        // set player-occupied grid sector to clean
        else if(currentMap[currentRow][currentCol] == Map::DIRTY)
        {
            currentMap[currentRow][currentCol] = Map::CLEAN;
        }

        // check for victory
        if(!playerWon && mapIsClean())
        {
                timeString.str("");
                timeString << gameTimer.getTicks() / 1000.2f << " seconds.";
                sTexts[TEXT_VICTORY2]->load(timeString.str().c_str(), {0,0,0});
                std::cout << "Player won in: " << gameTimer.getTicks() / 1000 << " seconds." << std::endl;
                gameTimer.stop();
                playerWon = true;
        }
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
                        sTextures[TEXTURE_CLEANFLOOR]->render(Map::GRID*col,Map::GRID*row);
                        sTextures[TEXTURE_DIRTYFLOOR]->render(Map::GRID*col,Map::GRID*row);
                        break;
                    case Map::CLEAN:
                        sTextures[TEXTURE_CLEANFLOOR]->render(Map::GRID*col,Map::GRID*row);
                        break;
                    case Map::BASE:
                        sTextures[TEXTURE_CLEANFLOOR]->render(Map::GRID*col,Map::GRID*row);
                        sTextures[TEXTURE_BASE]->render(Map::GRID*col,Map::GRID*row);
                        break;
                    default:
                        sTextures[TEXTURE_CLEANFLOOR]->render(Map::GRID*col,Map::GRID*row);
                    break;
                }
            }
        }

        //render robot
        sTextures[TEXTURE_ROBOBEAM]->render(sPlayer->getXPosition()-24, sPlayer->getYPosition()-24, NULL, -sPlayer->getDirection());
        sPlayer->render(sPlayer->getXPosition(), sPlayer->getYPosition(), NULL, -sPlayer->getDirection());
        // render furniture
        sTextures[TEXTURE_COUCH]->render(5*Map::GRID, 2*Map::GRID);
        sTextures[TEXTURE_TABLE]->render(6*Map::GRID, 7*Map::GRID);
        // render text/score
        if(playerWon)
        {
            sTexts[TEXT_VICTORY1]->render((Display::SCREEN_WIDTH-sTexts[TEXT_VICTORY1]->getWidth())/2, Display::SCREEN_HEIGHT/2-100);
            sTexts[TEXT_VICTORY2]->render((Display::SCREEN_WIDTH-sTexts[TEXT_VICTORY2]->getWidth())/2, Display::SCREEN_HEIGHT/2);
        }

    }

    void OneRoom::loadMedia()
    {
        std::cout << "Loading textures..." << std::endl;

        sTextures[TEXTURE_CLEANFLOOR] = new Media::Texture();
        // randomize floor texture
        srand (time(NULL));
        int floorOpt = rand() % 2;
        if(floorOpt==0) sTextures[TEXTURE_CLEANFLOOR]->load("ass/floor1.png");
        if(floorOpt==1) sTextures[TEXTURE_CLEANFLOOR]->load("ass/floor2.png");


        sTextures[TEXTURE_DIRTYFLOOR] = new Media::Texture();
        sTextures[TEXTURE_DIRTYFLOOR]->load("ass/floor_dirty.png");
        sTextures[TEXTURE_DIRTYFLOOR]->setAlpha(100);

        sTextures[TEXTURE_BASE] = new Media::Texture();
        sTextures[TEXTURE_BASE]->load("ass/base.png");

        sTextures[TEXTURE_COUCH] = new Media::Texture();
        sTextures[TEXTURE_COUCH]->load("ass/couch1.png");

        sTextures[TEXTURE_TABLE] = new Media::Texture();
        sTextures[TEXTURE_TABLE]->load("ass/table1.png");

        sTextures[TEXTURE_ROBOBEAM] = new Media::Texture();
        sTextures[TEXTURE_ROBOBEAM]->load("ass/robot_beam.png");
        sTextures[TEXTURE_ROBOBEAM]->setAlpha(100);

        std::cout << "\tdone." << std::endl;

        std::cout << "Loading sprites..." << std::endl;

        sPlayer = new Media::Player();
        sPlayer->load("ass/robot.png");

        std::cout << "\tdone." << std::endl;

        std::cout << "Loading music..." << std::endl;

        sMusic[MUSIC_CLAVIER] = new Media::Music();
        sMusic[MUSIC_CLAVIER]->load("ass/well-tempered-clavier.ogg");

        std::cout << "\tdone." << std::endl;

        std::cout << "Loading text..." << std::endl;

        sTexts[TEXT_VICTORY1] = new Media::Text();
        sTexts[TEXT_VICTORY1]->load("Your Time:", {0,0,0});

        sTexts[TEXT_VICTORY2] = new Media::Text();

        std::cout << "\tdone." << std::endl;

    }

    void OneRoom::loadMap()
    {
        currentMap = Map::MAP_ROOM_ONE;

        for(int row = 0; row < 15; row++)
        {
            for(int col = 0; col < 20; col++)
            {
                if(currentMap[row][col] == Map::BASE)
                {
                    sPlayer->setXPosition(col*Map::GRID);
                    sPlayer->setYPosition(row*Map::GRID);
                }
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
