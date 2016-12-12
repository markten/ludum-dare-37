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

        switch(currentMap[currentRow][currentCol])
        {
            case Map::OCCUPIED:
                sPlayer->moveBack();
                break;

            case Map::DIRTY:
                currentMap[currentRow][currentCol] = Map::CLEAN;
                break;

            case Map::BASE:
                if(mapIsClean())
                {
                    p_game->setPlayerWon(true);
                    p_game->setPlayerScore(gameTimer.getTicks()/1000.f);
                    gameTimer.stop();
                    p_game->popState();
                }
                break;

            case Map::POOP:
                streaking = true;
                sPlayer->setVelocity(2);
                break;

            default:
                break;
        }

        if(streaking)
        {
            frameCount++;
            if(frameCount == 15)
            {
                std::array<int,3> newPosition = {int(sPlayer->getXPosition()), int(sPlayer->getYPosition()), int(-sPlayer->getDirection())};
                streakPositions.push_back(newPosition);
                frameCount = 0;
            }
        }

    }

    void OneRoom::draw()
    {
        // render floor
        sTextures[TEXTURE_BACKGROUND]->render(0,0);
        for(int row = 0; row < 15; row++)
        {
            for(int col = 0; col < 20; col++)
            {
                switch(currentMap[row][col])
                {
                    case Map::DIRTY:
                        sTextures[TEXTURE_DIRTYFLOOR]->render(Map::GRID*col,Map::GRID*row);
                        break;
                    case Map::OCCUPIED:
                        sTextures[TEXTURE_DIRTYFLOOR]->render(Map::GRID*col,Map::GRID*row);
                        break;
                    case Map::POOP:
                        if(!streaking)
                        {
                            sTextures[TEXTURE_DIRTYFLOOR]->render(Map::GRID*col,Map::GRID*row);
                            sTextures[TEXTURE_POOP]->render(Map::GRID*col+10, Map::GRID*row+10);
                        }
                        break;
                    case Map::BASE:
                        sTextures[TEXTURE_BASE]->render(Map::GRID*col,Map::GRID*row);
                        break;
                    default:
                        // render nothing
                    break;
                }
            }
        }

        // render streaks
        for(int streak = 0; streak < streakPositions.size(); streak++)
        {
            sTextures[TEXTURE_STREAK]->render(streakPositions[streak][0], streakPositions[streak][1], NULL, streakPositions[streak][2]);
        }

        //render robot
        sTextures[TEXTURE_ROBOBEAM]->render(sPlayer->getXPosition()-24, sPlayer->getYPosition()-24, NULL, -sPlayer->getDirection());
        sPlayer->render(sPlayer->getXPosition(), sPlayer->getYPosition(), NULL, -sPlayer->getDirection());

        // render furniture
        sTextures[TEXTURE_COUCH]->render(5*Map::GRID, 2*Map::GRID);
        sTextures[TEXTURE_TABLE]->render(6*Map::GRID, 7*Map::GRID);
        sTextures[TEXTURE_LAMP]->render(2*Map::GRID, 2*Map::GRID);
        sTextures[TEXTURE_OTTOMAN]->render(5*Map::GRID, 10*Map::GRID);
        sTextures[TEXTURE_CHAIR]->render(16*Map::GRID, 4*Map::GRID);
        sTextures[TEXTURE_DESK]->render(17*Map::GRID, 2*Map::GRID);
        sTextures[TEXTURE_BED]->render(14*Map::GRID, 10*Map::GRID+10);
        sTextures[TEXTURE_DRESSER]->render(8*Map::GRID, 13*Map::GRID);
    }

    void OneRoom::loadMedia()
    {
        std::cout << "Loading textures..." << std::endl;

        sTextures[TEXTURE_BACKGROUND] = new Media::Texture();
        sTextures[TEXTURE_BACKGROUND]->load("ass/floor.png");
        // randomize floor texture
        srand (time(NULL));
        int floorR = rand() % 255 + 150;
        int floorG = rand() % 255 + 150;
        int floorB = rand() % 255 + 150;
        sTextures[TEXTURE_BACKGROUND]->setColor(floorR, floorG, floorB);

        sTextures[TEXTURE_DIRTYFLOOR] = new Media::Texture();
        sTextures[TEXTURE_DIRTYFLOOR]->load("ass/floor_dirty.png");
        sTextures[TEXTURE_DIRTYFLOOR]->setAlpha(100);

        sTextures[TEXTURE_BASE] = new Media::Texture();
        sTextures[TEXTURE_BASE]->load("ass/base.png");

        sTextures[TEXTURE_COUCH] = new Media::Texture();
        sTextures[TEXTURE_COUCH]->load("ass/couch.png");

        sTextures[TEXTURE_BED] = new Media::Texture();
        sTextures[TEXTURE_BED]->load("ass/bed.png");

        sTextures[TEXTURE_OTTOMAN] = new Media::Texture();
        sTextures[TEXTURE_OTTOMAN]->load("ass/ottoman.png");

        sTextures[TEXTURE_DESK] = new Media::Texture();
        sTextures[TEXTURE_DESK]->load("ass/desk.png");

        sTextures[TEXTURE_CHAIR] = new Media::Texture();
        sTextures[TEXTURE_CHAIR]->load("ass/chair.png");

        sTextures[TEXTURE_TABLE] = new Media::Texture();
        sTextures[TEXTURE_TABLE]->load("ass/table.png");

        sTextures[TEXTURE_DRESSER] = new Media::Texture();
        sTextures[TEXTURE_DRESSER]->load("ass/dresser.png");

        sTextures[TEXTURE_LAMP] = new Media::Texture();
        sTextures[TEXTURE_LAMP]->load("ass/lamp.png");

        sTextures[TEXTURE_ROBOBEAM] = new Media::Texture();
        sTextures[TEXTURE_ROBOBEAM]->load("ass/robot_beam.png");
        sTextures[TEXTURE_ROBOBEAM]->setAlpha(100);

        sTextures[TEXTURE_POOP] = new Media::Texture();
        sTextures[TEXTURE_POOP]->load("ass/poop.png");

        sTextures[TEXTURE_STREAK] = new Media::Texture();
        sTextures[TEXTURE_STREAK]->load("ass/streak.png");
        sTextures[TEXTURE_STREAK]->setAlpha(200);

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
