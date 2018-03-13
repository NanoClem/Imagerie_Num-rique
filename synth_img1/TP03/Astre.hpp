#ifndef ASTRE_HPP
#define ASTRE_HPP

#include <GL/glew.h>
#include <GL/freeglut.h>


class Astre {

    private:

        GLdouble rayon;
        GLfloat vitesse, distance, angle;
        GLfloat *rgb;

    public:

        Astre(GLdouble _rayon,
              GLfloat _vitesse, GLfloat _distance, GLfloat _angle,
              GLfloat *_rgb);
        ~Astre();

        void withSatellite(GLdouble satRayon,
                           GLfloat satVitesse, GLfloat satDistance, GLfloat satAngle,
                           GLfloat *satRGB);
        void withoutSatellite();

        inline GLdouble getRayon()    {return rayon;}
        inline GLfloat getVitesse()   {return vitesse;}
        inline GLfloat getDistance()  {return distance;}
        inline GLfloat getAngle()     {return angle;}
        inline GLfloat *getRGB()      {return rgb;}
};

#endif
