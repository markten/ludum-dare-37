#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <memory>
#include <SDL2/SDL.h>

#include "Game_State.hpp"
#include "../media/Image.hpp"
#include "../media/Texture.hpp"

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

            enum Textures
            {
                TEXTURE_TEST,
                TEXTURE_TOTAL
            };

            enum Sprites
            {
                SPRITE_PLAYER,
                SPRITE_TOTAL
            };

            enum Texts
            {
                TEXT_TEST,
                TEXT_TOTAL
            };

            enum Sounds
            {
                SOUND_TEST,
                SOUND_TOTAL
            };

            enum Music
            {
                MUSIC_TEST,
                MUSIC_TOTAL
            };
    };
}

#endif // MENU_HPP_INCLUDED
