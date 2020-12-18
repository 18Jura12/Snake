#include "game.h"
#include <iostream>

// Implementacija Game klase dolazi ovdje.

#include <stdexcept>

Game::Game(): mWindow(sf::VideoMode(600,600),"Snake"), mSnake(10), mWorld(sf::Vector2i(600,600))
{
    mTimePerFrame=sf::seconds(1.f/15.f);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen())
    {
  //      processEvents();
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate>mTimePerFrame)
        {
            timeSinceLastUpdate -= mTimePerFrame;
            processEvents();
            update(mTimePerFrame);
        }
        render();
    }
}

void Game::processEvents()
{
    // Process events
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        // Close window : exit
        switch(event.type){
        case sf::Event::Closed:
                mWindow.close();break;
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code);
            break;
        }
    }
}

void Game::update(sf::Time dt)
{
  mWorld.update(mSnake);
  mSnake.update();
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mSnake);
    mWindow.draw(mWorld);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key code)
{
    if(code == sf::Keyboard::Up && mSnake.getDirection()!=Direction::Down && mSnake.getDirection()!=Direction::None) mSnake.setDirection(Direction::Up);
    if(code == sf::Keyboard::Down && mSnake.getDirection()!=Direction::Up) mSnake.setDirection(Direction::Down);
    if(code == sf::Keyboard::Left && mSnake.getDirection()!=Direction::Right) mSnake.setDirection(Direction::Left);
    if(code == sf::Keyboard::Right && mSnake.getDirection()!=Direction::Left) mSnake.setDirection(Direction::Right);
}
