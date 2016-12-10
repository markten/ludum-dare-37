#include "GTimer.hpp"

#include <SDL2/SDL.h>
// Pretty much verbatim from the Lazy Foo' Tutorial on Timers


GTimer::GTimer()
: startTime(0)
, pauseTime(0)
, paused(false)
, started(false)
{

}

GTimer::~GTimer()
{

}

void GTimer::start()
{
    started = true;
    paused = false;
    startTime = SDL_GetTicks();
    pauseTime = 0;
}

void GTimer::stop()
{
    started = false;
    paused = false;
    startTime = 0;
    pauseTime = 0;
}

void GTimer::pause()
{
    if(started && !paused)
    {
        paused = true;
        pauseTime = SDL_GetTicks() - startTime;
        startTime = 0;
    }
}

void GTimer::resume()
{
    if(started && paused)
    {
        paused = false;
        startTime = SDL_GetTicks() - pauseTime;
        pauseTime = 0;
    }
}

uint32_t GTimer::getTicks()
{
    uint32_t time = 0;

    if(started)
    {
        if(paused)
        {
            time = pauseTime;
        }
        else
        {
            time = SDL_GetTicks() - startTime;
        }
    }

    return time;
}

bool GTimer::isStarted()
{
    return started;
}

bool GTimer::isPaused()
{
    return paused && started;
}
