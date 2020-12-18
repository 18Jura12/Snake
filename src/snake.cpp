#include "snake.h"
#include <iostream>

//  Implementacija klase Snake dolazi ovdje.

Snake::Snake(int blockSize)
{

    sf::Vector2f a(blockSize,blockSize);
    mbodyRect.setSize(a);
    mSnakeBody.push_back(SnakeSegment(3,5));
    mSnakeBody.push_back(SnakeSegment(3,4));
    mSnakeBody.push_back(SnakeSegment(3,3));
    msize=blockSize;
    mdir=Direction::None;
    mspeed=10;
    mlives=3;
    mscore=0;
    mlost=false;
}

sf::Vector2i Snake::getPosition()
{
    sf::Vector2i rez(mSnakeBody.front().x,mSnakeBody.front().y);
    return rez;
}

void Snake::extend()
{
    int duljina=mSnakeBody.size();
    SnakeSegment novi(mSnakeBody[duljina-2].x-mSnakeBody[duljina-1].x,mSnakeBody[duljina-1].y-mSnakeBody[duljina-2].y);
    novi.x=mSnakeBody.back().x-novi.x;
    novi.y=mSnakeBody.back().y-novi.y;
    mSnakeBody.push_back(novi);
}

void Snake::reset()
{
    mSnakeBody.clear();
    //mozda desturktor prije
    //mozda umjesto konstruktor copypaste konstruktor
    msize=10;
    sf::Vector2f a(msize,msize);
    mbodyRect.setSize(a);
    mSnakeBody.push_back(SnakeSegment(3,5));
    mSnakeBody.push_back(SnakeSegment(3,4));
    mSnakeBody.push_back(SnakeSegment(3,3));
    mdir=Direction::None;
    mspeed=10;
    mlives=3;
    mscore=0;
    mlost=false;

}

void Snake::update(){

    move();
    checkCollision();
    }

void Snake::cut(int n)
{
   while(n){
       n--;
       mSnakeBody.pop_back();
   }
}

void Snake::move()
{
    int i;
    for(i=mSnakeBody.size()-1;i>0;--i){
        mSnakeBody[i].x=mSnakeBody[i-1].x;
        mSnakeBody[i].y=mSnakeBody[i-1].y;
    }
    switch(mdir)
    {
    case Direction::Left: {mSnakeBody[0].x--;break;}
    case Direction::Right: {mSnakeBody[0].x++;break;}
    case Direction::Up: {mSnakeBody[0].y--;break;}
    case Direction::Down: {mSnakeBody[0].y++;break;}
    case Direction::None: {reset();break;}
    default: break;
    }

}

void Snake::checkCollision()
{
    if(mdir==Direction::None) return;
    for (int i=1;i<mSnakeBody.size()-1;i++){
       if(mSnakeBody[0].x==mSnakeBody[i].x && mSnakeBody[0].y==mSnakeBody[i].y)
       { if(!(--mlives)) mlost=true; cut(mSnakeBody.size()-i);}
    }
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    mbodyRect.setFillColor(sf::Color::Green);
    sf::Vector2f a(mSnakeBody[0].x*10+10,mSnakeBody[0].y*10+10);
    mbodyRect.setPosition(a);
    target.draw(mbodyRect);
    mbodyRect.setFillColor(sf::Color::Yellow);
    for(int i=1;i!=mSnakeBody.size();i++) {
        a.x=mSnakeBody[i].x*10+10;
        a.y=mSnakeBody[i].y*10+10;
        mbodyRect.setPosition(a);
        target.draw(mbodyRect);
    }

}




