//
//  Walker.cpp
//  FM_Visuals
//
//  Created by Phillip Short on 28/03/2022.
//

#include "Walker.hpp"

//pass mouse x & y positions to constructor and init all private member variables
Walker::Walker(float _x, float _y)
{
    x = _x;
    y = _y;
    px = x;
    py = y;
    velX = ofRandom(-5, 5);
    velY = ofRandom(-5, 5);
    life = 255;
}

//return true if walker has left the bounds of the canvas
bool Walker::isOut()
{
    return (x < 0 || x > ofGetWidth() || y < 0 || y > ofGetHeight());
}

//use noise function to generate some fluid movment.
void Walker::velocity()
{
    velX += ofMap(ofNoise(x * 0.003, y * 0.003), 0, 1, -1, 1);
    velY += ofMap(ofNoise(y * 0.003, x * 0.003), 0, 1, -1, 1);
}

//move walker
void Walker::move()
{
    x += velX;
    y += velY;
}

//because the background is constantly being re-drawn before the walker, I need to keep track of where the walkers been so i can draw its path to the canvas. I keep a history of the walkers movments in the posVec vector which is being filled with an object containing x, y & previous x & y positions.
void Walker::update()
{
    posVec.push_back(createObj(x, y, px, py));
}

//reduces life variable. this is used to reduce the walkers color alpha value
void Walker::reduceLifeSpan()
{
    life -= 0.65;
}

//when life reaches 0 return true
bool Walker::lifeSpan()
{
    return life >= 0;
}

//draw walker to canvas
void Walker::draw ()
{
    ofSetColor(255, 125, 255, life);
    //loop through posVec vector, draw line using x, y, previous x and previous y. Then switch x and y to previous x and y so the two swap over every time draw is called
    for (int i = 0; i < posVec.size(); i++)
    {
      ofDrawLine(posVec[i].x, posVec[i].y,
                 posVec[i].px, posVec[i].py);
      
      px = posVec[i].x;
      py = posVec[i].y;
    }
}

//empty posVec vector
void Walker::emptyPosVec()
{
    posVec.clear();
}

//createObj is a function of type Obj declared in walker.hpp, it creates a new Obj instance and inits their values to thoose that are passed in to the function as arguments. It stores the x, y & previous x, y positions at any one time.
Obj createObj(float _x, float _y, float _px, float _py)
{
    Obj obj;
    obj.x = _x;
    obj.y = _y;
    obj.px = _px;
    obj.py = _py;
    return obj;
}
