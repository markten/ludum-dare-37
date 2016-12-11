#ifndef SCORES_HPP_INCLUDED
#define SCORES_HPP_INCLUDED

#include "../Game.hpp"

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
            double currentScore = 0.0;

            enum Textures
            {
                TEXTURE_TOTAL
            };

            enum Sprites
            {
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

            enum MUSIC_CLAVIER
            {
                MUSIC_TOTAL
            };
    };
}

#endif // SCORES_HPP_INCLUDED
