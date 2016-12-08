#ifndef GAME_STATE_HPP_INCLUDED
#define GAME_STATE_HPP_INCLUDED

class Game;

#include "../media/Texture.hpp"
#include "../media/Sprite.hpp"
#include "../media/Text.hpp"

#include <memory>
#include <vector>

namespace State
{
    class Game_State
    {
        public:
            Game_State(Game& game,
                       uint16_t numTextures,
                       uint16_t numTexts);
            ~Game_State();

            virtual void input() = 0;
            virtual void update() = 0;
            virtual void draw() = 0;
            virtual void loadMedia() = 0;

        protected:
            Game* p_game;
            std::vector<Media::Texture*> sTextures;
            //std::unique_ptr<Media::Sprite*[]> sSprites;
            std::vector<Media::Text*> sTexts;
    };

}

#endif // GAME_STATE_HPP_INCLUDED
