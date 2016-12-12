#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "media/Sprite.hpp"

namespace Media
{
    class Player : public Sprite
    {
        public:
            Player();
            ~Player();

            void update() override;
            void moveBack();

            void setGoingForward(bool status);
            void setGoingBackward(bool status);
            void setTurningRight(bool status);
            void setTurningLeft(bool status);
            //void collide(std::array currentMap);

        private:
            bool goingForward = false;
            bool goingBackward = false;
            bool turningRight = false;
            bool turningLeft = false;
    };
}

#endif // PLAYER_HPP_INCLUDED
