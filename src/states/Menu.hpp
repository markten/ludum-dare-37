#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "Game_State.hpp"

class Game;

namespace State
{
    class Menu : public Game_State
    {
        public:
            Menu(Game& game);

            void input() override;
            void update() override;
            void draw() override;

        private:

    };
}

#endif // MENU_HPP_INCLUDED
