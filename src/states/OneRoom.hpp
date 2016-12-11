#ifndef ONEROOM_HPP_INCLUDED
#define ONEROOM_HPP_INCLUDED

#include "Game_State.hpp"

#include <array>

namespace State
{
    class OneRoom : public Game_State
    {
        public:
            OneRoom(Game& game);
            ~OneRoom();

            void input() override;
            void update() override;
            void draw()override;

        private:
            void loadMedia() override;
            void loadMap();
            void printMap();
            bool mapIsClean();

            std::array<std::array<int,20>,15> currentMap;
            std::array<std::array<int,20>,15> currentMapRotations;

            enum Textures
            {
                TEXTURE_DIRTYFLOOR,
                TEXTURE_CLEANFLOOR,
                TEXTURE_BASE,
                TEXTURE_TOTAL
            };

            enum Sprites
            {
                SPRITE_PLAYER,
                SPRITE_TOTAL
            };

            enum Texts
            {
                TEXT_TOTAL
            };

            enum Sounds
            {
                SOUND_TOTAL
            };

            enum Music
            {
                MUSIC_CLAVIER,
                MUSIC_TOTAL
            };

    };
}

#endif // ONEROOM_HPP_INCLUDED
