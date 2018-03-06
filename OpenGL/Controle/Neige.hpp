#ifndef NEIGE_HPP
#define NEIGE_HPP

#include <iostream>
#include <list>
using namespace std;
#include "Texture.hpp"
#include "Flocon.hpp"


class Neige {

  private:
    float xmin, ymin, zmin, xmax, ymax, zmax;
    list<Flocon> floconList;
    float emissionTime, elapsedTime;
    Texture *floconTexture;

  public:
    Neige(float _xmin, float _ymin, float _zmin, float _xmax, float _ymax, float _zmax, list<Flocon>& _floconList,
          float _emissionTime, float _elapsedTime, Texture *_floconTexture);
    ~Neige();
    void anime(float timeFrame);
    void show();
    void loadTex();

    //Getters et Setters
    inline void setXmin(float _xmin) {xmin = _xmin;}
    inline void setYmin(float _ymin) {ymin = _ymin;}
    inline void setZmin(float _zmin) {zmin = _zmin;}
    inline void setXmax(float _xmax) {xmax = _xmax;}
    inline void setYmax(float _ymax) {ymax = _ymax;}
    inline void setZmax(float _zmax) {zmax = _zmax;}
    inline void setElapsed(float _elapsedTime)  {elapsedTime = _elapsedTime;}
    inline void setEmission(float _emissionTime) {emissionTime = _emissionTime;}

    inline float getXmin() {return xmin;}
    inline float getYmin() {return ymin;}
    inline float getZmin() {return zmin;}
    inline float getXmax() {return xmax;}
    inline float getYmax() {return ymax;}
    inline float getZmax() {return zmax;}
    inline float getEmission() {return emissionTime;}
    inline float getElapsed() {return elapsedTime;}
};

#endif
