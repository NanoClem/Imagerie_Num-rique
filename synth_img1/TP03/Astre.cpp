#include "Astre.hpp"


//Constructeur
Astre::Astre(GLdouble _rayon, GLfloat _vitesse, GLfloat _distance, GLfloat _angle, GLfloat *_rgb)
    : rayon(_rayon), vitesse(_vitesse), distance(_distance), angle(_angle), rgb(_rgb)
{}


//Destructeur
Astre::~Astre()
{
  delete [] rgb;
}


//Dessin d'un astre sans satellite
void Astre::withoutSatellite()
{
  glPushMatrix();
      glColor3f(rgb[0], rgb[1], rgb[2]);         //Couleur de l'astre                                         //couleur de l'astre
      glRotatef(vitesse*angle, 0.0, 1.0, 0.0);   //rotation de l'astre autour de Oy
      glTranslatef(distance, 0.0, 0.0);          //Distance par rapport à (0,0,0) ou au Soleil
      glutSolidSphere(rayon, 10.0, 10.0);         //Creation de l'astre
  glPopMatrix();
}


//Dessin d'un astre avec satellite en orbite
void Astre::withSatellite()
{
  glPushMatrix();
      //Astre
      glColor3f(rgb[0], rgb[1], rgb[2]);         //Couleur de l'astre                                         //couleur de l'astre
      glRotatef(vitesse*angle, 0.0, 1.0, 0.0);   //rotation de l'astre autour de Oy
      glTranslatef(distance, 0.0, 0.0);          //Distance par rapport à (0,0,0) ou au Soleil
      glutSolidSphere(rayon, 10.0, 10.0);         //Creation de l'astre

      //satellite
      glColor3f(1.0, 1.0, 1.0);
      glRotatef(vitesse*2.0*angle, 0.0, 1.0, 1.0);
      glTranslatef(1.2, 0.0, 0.0);
      glutSolidSphere(rayon/2, 10.0, 10.0);
  glPopMatrix();
}
