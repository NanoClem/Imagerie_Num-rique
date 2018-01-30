#ifndef SMOKE_HPP
#define SMOKE_HPP

#include <iostream>
using namespace std;
#include "Texture.hpp"
#include "Breath.hpp"


class Smoke {

  private:
    float x, y, z;
    list<Breath> breathList;
    float emissionTime, elapsedTime;
    Texture *breathTexture;

  public:
    Smoke(float _x, float _y, float _z, list<Breath>& _breathList,
          float _emissionTime, float _elapsedTime, Texture& _breathTexture);
    ~Smoke();
    void anime(float timeFrame);
    void show();

    //Getters et Setters
    inline void setX(float _x) {x = _x;}
    inline void setY(float _y) {y = _y;}
    inline void setZ(float _z) {z = _z;}
    inline void setElapsed(float _elapsedTime)  {elapsedTime = _elapsedTime;}
    inline void setEmission(float _emissionTime) {emissionTime = _emissionTime;}

    inline float getX() {return x;}
    inline float getY() {return y;}
    inline float getZ() {return z;}
    inline float getEmission() {return emissionTime;}
    inline float getElapsed() {return elapsed;}
};

#endif
