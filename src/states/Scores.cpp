#include "Scores.hpp"

#include "../media/Text.hpp"
#include "../Display.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

namespace State
{
    Scores::Scores(Game& game)
    : Game_State(game, TEXTURE_TOTAL, SPRITE_TOTAL, TEXT_TOTAL, SOUND_TOTAL, MUSIC_TOTAL)
    {
        loadScores();
        if(p_game->getPlayerScore() != 0) saveScores();
        loadMedia();
    }

    Scores::~Scores()
    {

    }

    void Scores::input()
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
                        p_game->popState();
                    break;

                    default:
                        // do nothing
                    break;
                }
            }
        }
    }

    void Scores::update()
    {

    }

    void Scores::draw()
    {
        // draw background
        sTextures[TEXTURE_BACKGROUND]->render(0,0);

        // draw scores
        sTexts[TEXT_PLAYERSCORE]->render((Display::SCREEN_WIDTH-sTexts[TEXT_PLAYERSCORE]->getWidth())/2,125);
        sTexts[TEXT_SCORE0]->render((Display::SCREEN_WIDTH-sTexts[TEXT_SCORE0]->getWidth())/2,350);
        sTexts[TEXT_SCORE1]->render((Display::SCREEN_WIDTH-sTexts[TEXT_SCORE1]->getWidth())/2,400);
        sTexts[TEXT_SCORE2]->render((Display::SCREEN_WIDTH-sTexts[TEXT_SCORE2]->getWidth())/2,450);
    }

    void Scores::loadMedia()
    {
        std::cout << "Loading textures..." << std::endl;

        sTextures[TEXTURE_BACKGROUND] = new Media::Texture();
        sTextures[TEXTURE_BACKGROUND]->load("ass/score_background.png");

        std::cout << "\tdone." << std::endl;

        std::cout << "Loading text..." << std::endl;

        std::ostringstream scoreString;
        scoreString << p_game->getPlayerScore() << "s";

        SDL_Color textColor = {0,0,0,255};
        sTexts[TEXT_PLAYERSCORE] = new Media::Text();
        sTexts[TEXT_PLAYERSCORE]->load(scoreString.str().c_str(), textColor);

        sTexts[TEXT_SCORE0] = new Media::Text();
        sTexts[TEXT_SCORE0]->load(topScores[0].str(), textColor);

        sTexts[TEXT_SCORE1] = new Media::Text();
        sTexts[TEXT_SCORE1]->load(topScores[1].str(), textColor);

        sTexts[TEXT_SCORE2] = new Media::Text();
        sTexts[TEXT_SCORE2]->load(topScores[2].str(), textColor);

        std::cout << "\tdone." << std::endl;
    }

    void Scores::loadScores()
    {
        std::fstream scoreFile("scores.txt");
        std::string line;

        if (scoreFile.is_open())
        {
            for(int index = 0; index < 3; index++)
            {
                std::getline(scoreFile, line);
                topScores[index] << line << "s";
            }
        }
        else
        {
            std::cout << "Error opening score file. Loading default values." <<std::endl;
            topScores[0] << 121.00 << "s";
            topScores[1] << 131.00 << "s";
            topScores[2] << 141.00 << "s";
        }

        scoreFile.close();
    }

    void Scores::saveScores()
    {
        std::vector<double> allScores(4);

        allScores[3] = p_game->getPlayerScore();

        // load high scores
        for(int index = 0; index < 3; index++)
        {
            topScores[index] >> allScores[index];
            //allScores[index] = std::stod(topScores[index].str(), nullptr);
        }

        // sort scores
        std::sort(allScores.begin(), allScores.end());

        // save top 3 scores to file
        std::fstream scoreFile("scores.txt");

        if(scoreFile.is_open())
        {
            for(int index = 0; index < 3; index++)
            {
                scoreFile << allScores[index] << std::endl;
            }
        }
        scoreFile.close();
    }
}
