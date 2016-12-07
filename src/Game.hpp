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

    private:
        std::stack<std::unique_ptr<State::Game_State>> gameStates;
};

#endif // GAME_HPP_INCLUDED
