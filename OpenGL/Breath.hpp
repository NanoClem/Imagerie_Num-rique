#ifndef BREATH_HPP
#define BREATH_HPP

class Breath {

  private:
    float xpos, ypos, zpos;
    float size;
    float xspeed, yspeed, zspeed;
    float lifeTime;

  public:
    Breath(float _xpos, float _ypos, float _zpos,
          float _size,
          float _xspeed, float _yspeed, float _zspeed,
          float _lifeTime);
    ~Breath();
    void anime(float timeFrame);
    void show();

    //Getters et Setters
    inline void setSize(float _size)         {size     = _size;}
    inline void setLifeTime(float _lifeTime) {lifeTime = _lifeTime;}
    inline void setxPos(float _xpos)         {xpos     = _xpos;}
    inline void setyPos(float _ypos)         {ypos     = _ypos;}
    inline void setzPos(float _zpos)         {zpos     = _zpos;}
    inline void setxSpeed(float _xspeed)     {xspeed   = _xspeed;}
    inline void setySpeed(float _yspeed)     {yspeed   = _yspeed;}
    inline void setzSpeed(float _zspeed)     {zspeed   = _zspeed;}

    inline float getSize()     {return size;}
    inline float getLifeTime() {return lifeTime;}
    inline float getxPos()     {return xpos;}
    inline float getyPos()     {return ypos;}
    inline float getzPos()     {return zpos;}
    inline float getxSpeed()   {return xspeed;}
    inline float getySpeed()   {return yspeed;}
    inline float getzSpeed()   {return zspeed;}
};

#endif
