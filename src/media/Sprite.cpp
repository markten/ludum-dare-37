#include "Sprite.hpp"

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

    void Sprite::setAnimating(bool animate)
    {
        animating = animate;
    }

    void Sprite::setXVelocity(int xVel)
    {
        xVelocity = xVel;
    }

    void Sprite::setYVelocity(int yVel)
    {
        yVelocity = yVel;
    }

    int Sprite::getXPosition()
    {
        return xPosition;
    }

    int Sprite::getYPosition()
    {
        return yPosition;
    }

    void Sprite::update()
    {
        xPosition += xVelocity;
        yPosition += yVelocity;

        frameCount++;
        if(frameCount >= totalFrames) frameCount = 0;
    }


}
