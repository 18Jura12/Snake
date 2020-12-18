#include "world.h"
#include <ctime>
#include <random>

// Implementacija klase World dolazi ovdje.


World::World(sf::Vector2i windowSize)
{
    mWindowSize.x=windowSize.x;
    mWindowSize.y=windowSize.y;
    mApple.setRadius(5);
    mApple.setFillColor(sf::Color::Red);

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1,58);
    int random_x=uniform_dist(e1);
    int random_y=uniform_dist(e1);
    mApple.setPosition(random_x*10,random_y*10);

    sf::Vector2f a(mWindowSize.x, 10);
    mBounds[0].setSize(a);
    sf::Vector2f b(10, mWindowSize.y-10);
    mBounds[1].setSize(b);
    sf::Vector2f c(mWindowSize.x, 10);
    mBounds[2].setSize(c);
    sf::Vector2f d(10, mWindowSize.y-10);
    mBounds[3].setSize(d);
    for(int i=0; i<4;i++) mBounds[i].setFillColor(sf::Color::Red);
    mBounds[0].setPosition(0,0);
    mBounds[1].setPosition(0,9);
    mBounds[2].setPosition(0,590);
    mBounds[3].setPosition(590,9);

}

void World::respawnApple()
{

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1,58);
    int random_x=uniform_dist(e1);
    int random_y=uniform_dist(e1);
    mApple.setPosition(random_x*10,random_y*10);
}

void World::update(Snake &snake)
{
    if(snake.getPosition().x*10+10==0 || snake.getPosition().y*10+10==0 || snake.getPosition().x*10+10==590 || snake.getPosition().y*10+10==590){
        snake.lose();
    }

    if(mBlockSize*snake.getPosition().x==mApple.getPosition().x-10 && mBlockSize*snake.getPosition().y==mApple.getPosition().y-10){
        snake.extend();
        respawnApple();
    }
    if(snake.hasLost()){
        snake.reset();
        respawnApple();
    }

}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0; i<4; ++i)
      target.draw(mBounds[i]);
    target.draw(mApple);
}
