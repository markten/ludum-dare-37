#ifndef GAME_STATE_HPP_INCLUDED
#define GAME_STATE_HPP_INCLUDED

class Game;

namespace State
{
    class Game_State
    {
        public:
            Game_State(Game& game);

            virtual void input() = 0;
            virtual void update() = 0;
            virtual void draw() = 0;

        protected:
            Game* p_game;
    };

}

#endif // GAME_STATE_HPP_INCLUDED
