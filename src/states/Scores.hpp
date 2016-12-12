#ifndef SCORES_HPP_INCLUDED
#define SCORES_HPP_INCLUDED

#include "../Game.hpp"

#include <array>
#include <sstream>

namespace State
{
    class Scores : public Game_State
    {
        public:
            Scores(Game& game);
            ~Scores();

            void input() override;
            void update() override;
            void draw() override;
            void loadMedia() override;

        private:
            void loadScores();
            void saveScores();
            std::array<std::stringstream, 3> topScores;

            enum Textures
            {
                TEXTURE_BACKGROUND,
                TEXTURE_TOTAL
            };

            enum Sprites
            {
                SPRITE_TOTAL
            };

            enum Texts
            {
                TEXT_PLAYERSCORE,
                TEXT_SCORE0,
                TEXT_SCORE1,
                TEXT_SCORE2,
                TEXT_TOTAL
            };

            enum Sounds
            {
                SOUND_TOTAL
            };

            enum MUSIC_CLAVIER
            {
                MUSIC_TOTAL
            };
    };
}

#endif // SCORES_HPP_INCLUDED
