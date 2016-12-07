#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <memory>
#include <SDL2/SDL.h>

#include "Game_State.hpp"
#include "../media/Image.hpp"

class Game;

namespace State
{
    class Menu : public Game_State
    {
        public:
            Menu(Game& game);
            ~Menu();

            void input() override;
            void update() override;
            void draw() override;

        private:
            std::unique_ptr<Media::Image*[]> imageSurfaces;
    };
}

#endif // MENU_HPP_INCLUDED
