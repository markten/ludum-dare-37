#include "Game_State.hpp"

#include <memory>

namespace State
{

    Game_State::Game_State(Game& game,
                           uint16_t numTextures,
                           uint16_t numSprites,
                           uint16_t numTexts)
    : p_game(&game)
    , sTextures(numTextures)
    , sSprites(numSprites)
    , sTexts(numTexts)
    {

    }

    Game_State::~Game_State()
    {
        // free memory from loaded media
        for(uint16_t i = 0; i < sTextures.size(); i++)
        {
            delete(sTextures[i]);
        }

        for(uint16_t i = 0; i < sSprites.size(); i++)
        {
            delete(sSprites[i]);
        }

        for(uint16_t i = 0; i < sTexts.size(); i++)
        {
            delete(sTexts[i]);
        }

    }

}
