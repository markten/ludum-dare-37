#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <memory>
#include <SDL2/SDL.h>

#include "Game_State.hpp"

//class Game;

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
            void loadMedia() override;
            int frameCount = 0;
            bool displayText = true;
            bool displayHelp = false;
            bool playerWon = false;

            enum Textures
            {
                TEXTURE_BACKGROUND,
                TEXTURE_HELP,
                TEXTURE_TOTAL
            };

            enum Sprites
            {
                SPRITE_TOTAL
            };

            enum Texts
            {
                TEXT_ENTER,
                TEXT_HELP,
                TEXT_TOTAL
            };

            enum Sounds
            {
                SOUND_TOTAL
            };

            enum Music
            {
                MUSIC_TITLE,
                MUSIC_TOTAL
            };
    };
}

#endif // MENU_HPP_INCLUDED
