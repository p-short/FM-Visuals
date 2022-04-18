//
//  Walker.hpp
//  FM_Visuals
//
//  Created by Phillip Short on 28/03/2022.
//

#ifndef Walker_hpp
#define Walker_hpp

#include <stdio.h>
#include "ofMain.h"

//struct called Obj, this is used later so I can push an object in to a vector
struct Obj
{
public:
    float x, y, px, py;
};

//function of type Obj, this is defined in Walker.cpp
Obj createObj(float _x, float _y, float _px, float _py);

//Walker class. This code was very much inspired by a adaptation on random walks by Mamboleoo on generativehut.com, found here https://www.generativehut.com/post/random-walkers the code was adapted from javaScript to C++ and Ive changed aspects of the code along the way but the courseworks genesis was from first experimenting with said tutorial.
class Walker {
public:
    Walker(float _x, float _y);
    bool isOut();
    void velocity();
    void move();
    void update();
    void reduceLifeSpan();
    bool lifeSpan();
    void draw();
    void emptyPosVec();
    
private:
    float x, y, px, py, velX, velY, life;
    vector<Obj> posVec;
};

#endif /* Walker_hpp */

