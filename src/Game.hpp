#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <memory>
#include <stack>

#include "states/Game_State.hpp"

class Game
{
    public:
        Game();

        void runMainGameLoop();
        void pushState(std::unique_ptr<State::Game_State>);
        void popState();
        void quitGame();
        void setPlayerWon(bool state);
        bool getPlayerWon();
        void setPlayerScore(double score);
        double getPlayerScore();

    private:
        std::stack<std::unique_ptr<State::Game_State>> gameStates;
        bool quit = false;
        bool playerWon = false;
        double playerScore = 0.0;
};

#endif // GAME_HPP_INCLUDED
