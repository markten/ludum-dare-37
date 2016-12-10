#ifndef GTIMER_HPP_INCLUDED
#define GTIMER_HPP_INCLUDED

#include <cstdint>

class GTimer
{
    public:
        GTimer();
        ~GTimer();

        void start();
        void stop();
        void pause();
        void resume();

        uint32_t getTicks();

        bool isStarted();
        bool isPaused();

    private:

        uint32_t startTime;
        uint32_t pauseTime;

        bool paused;
        bool started;
};

#endif // TIMER_HPP_INCLUDED
