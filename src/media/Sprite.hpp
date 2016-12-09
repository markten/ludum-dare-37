#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED

#include "Media_Object.hpp"
#include "Texture.hpp"

#include <vector>
#include <SDL2/SDL.h>

namespace Media
{
    class Sprite : public Texture
    {
        public:
            Sprite(uint16_t numClipRects, uint16_t numCollisionRects);
            ~Sprite();

            void update();
            std::vector<SDL_Rect> getCollisionRects();
            void setAnimating(bool animate);
            void setXVelocity(int xVel);
            void setYVelocity(int yVel);
            int getXPosition();
            int getYPosition();

        private:
            std::vector<SDL_Rect> clipRects;
            std::vector<SDL_Rect> collisionRects;

            uint16_t currentClipRect = 0;

            bool animating = true;
            uint32_t frameCount = 0;
            uint32_t totalFrames = 1;

            int xVelocity = 0;
            int yVelocity = 0;

            int xPosition = 0;
            int yPosition = 0;
    };
}

#endif // SPRITE_HPP_INCLUDED
