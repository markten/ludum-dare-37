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

            virtual void update();
            std::vector<SDL_Rect> getCollisionRects();
            void setVelocity(int newVelocity);
            void setDirection(int newDirection);
            void incrementDirection(double increment);
            int getXPosition();
            int getYPosition();
            void setXPosition(int newXPosition);
            void setYPosition(int newYPosition);
            double getDirection();

        protected:
            std::vector<SDL_Rect> clipRects;
            std::vector<SDL_Rect> collisionRects;

            uint16_t currentClipRect = 0;

            int mVelocity = 0;
            double mDirection = 0;

            int xPosition = 300;
            int yPosition = 400;
    };
}

#endif // SPRITE_HPP_INCLUDED
