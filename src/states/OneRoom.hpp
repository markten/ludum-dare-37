#ifndef ONEROOM_HPP_INCLUDED
#define ONEROOM_HPP_INCLUDED

#include "Game_State.hpp"

#include <array>
#include <vector>

#include "../GTimer.hpp"

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
            int frameCount = 0;
            bool streaking = false;

            GTimer gameTimer;

            std::array<std::array<int,20>,15> currentMap;
            std::vector<std::array<int,3>> streakPositions;

            enum Textures
            {
                TEXTURE_BACKGROUND,
                TEXTURE_DIRTYFLOOR,
                TEXTURE_BASE,
                TEXTURE_COUCH,
                TEXTURE_DESK,
                TEXTURE_OTTOMAN,
                TEXTURE_BED,
                TEXTURE_TABLE,
                TEXTURE_DRESSER,
                TEXTURE_LAMP,
                TEXTURE_CHAIR,
                TEXTURE_ROBOBEAM,
                TEXTURE_POOP,
                TEXTURE_STREAK,
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
