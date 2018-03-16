#ifndef CERCLEDIR_HPP
#define CERCLEDIR_HPP

class CercleDir {

    private :

        float rayon
        float centreX, centreY;

    public :

        CercleDir(float _rayon, float _centreX, float _centreY)
            : rayon(_rayon), centreX(_centreX), centreY(_centreY)
        {}

        inline ~CercleDir() {}
        void makeDirection(float *coords, float angleStep);

        inline float getRayon()   const   {return rayon;}
		inline float getCentreX() const   {return centreX;}
        inline float getCentreY() const   {return centreY;}

        inline void setRayon(float _rayon)      {rayon = _rayon;}
        inline void setCentreX(float _centreX)  {centreX = _centreX;}
        inline void setCentreY(float _centreY)  {centreY = _centreY;}
};


#endif
