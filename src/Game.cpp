#include "Game.hpp"
#include "Display.hpp"
#include "states/Menu.hpp"


Game::Game()
{
    pushState(std::make_unique<State::Menu>(*this));
}

void Game::runMainGameLoop()
{
    while(!quit)
    {
        gameStates.top()->input();
        //gameStates.top()->update();
        gameStates.top()->draw();

        Display::update();
    }
}

void Game::pushState(std::unique_ptr<State::Game_State> state)
{
    gameStates.push(std::move(state));
}

void Game::popState()
{
    gameStates.pop();
}

void Game::quitGame()
{
    quit = true;
}



