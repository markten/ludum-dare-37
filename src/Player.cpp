#include "Player.hpp"

#define PI 3.14159265

#include <cmath>
#include <iostream>

namespace Media
{
    Player::Player()
    : Sprite(0,0)
    {

    }

    Player::~Player()
    {

    }

    void Player::update()
    {
        if(turningRight && !turningLeft)
        {
            incrementDirection(-mIncrement);
        }
        else if(!turningRight && turningLeft)
        {
            incrementDirection(mIncrement);
        }
        else if(turningRight && turningLeft)
        {

        }
        else if(!turningRight && ! turningLeft)
        {

        }

        if(goingForward && !goingBackward)
        {
            xPosition -= mVelocity * sin(PI*mDirection/180);
            yPosition -= mVelocity * cos(PI*mDirection/180);
        }
        else if(!goingForward && goingBackward)
        {
            xPosition += mVelocity * sin(PI*mDirection/180);
            yPosition += mVelocity * cos(PI*mDirection/180);
        }

    }

    void Player::setGoingForward(bool status)
    {
        goingForward = status;
    }

    void Player::setGoingBackward(bool status)
    {
        goingBackward = status;
    }

    void Player::setTurningRight(bool status)
    {
        turningRight = status;
    }

    void Player::setTurningLeft(bool status)
    {
        turningLeft = status;
    }

}
