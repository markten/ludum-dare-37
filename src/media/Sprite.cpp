#include "Sprite.hpp"

#include <cmath>

#define PI 3.14159265

namespace Media
{
    Sprite::Sprite(uint16_t numClipRects, uint16_t numCollisionRects)
    : clipRects(numClipRects)
    , collisionRects(numCollisionRects)
    {

    }

    Sprite::~Sprite()
    {

    }

    std::vector<SDL_Rect> Sprite::getCollisionRects()
    {
        return collisionRects;
    }

    void Sprite::setVelocity(double newVelocity)
    {
        mVelocity = newVelocity;
    }

    void Sprite::setDirection(double increment)
    {
        // maybe update to maintain bounds
        mDirection += increment;
    }

    void Sprite::incrementDirection(double increment)
    {
        mDirection += increment;
    }

    double Sprite::getXPosition()
    {
        return xPosition;
    }

    double Sprite::getYPosition()
    {
        return yPosition;
    }

    void Sprite::setXPosition(double newXPosition)
    {
        xPosition = newXPosition;
    }

    void Sprite::setYPosition(double newYPosition)
    {
        yPosition = newYPosition;
    }

    double Sprite::getDirection()
    {
        return mDirection;
    }

    void Sprite::update()
    {
        xPosition += mVelocity * cos((180/PI)*mDirection);
        yPosition += mVelocity * sin((180/PI)*mDirection);
    }


}
