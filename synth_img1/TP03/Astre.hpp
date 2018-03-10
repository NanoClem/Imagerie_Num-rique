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

        void withSatellite();
        void withoutSatellite();
};

#endif
