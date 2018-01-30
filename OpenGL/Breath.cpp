#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Breath.hpp"


///////////////////////////////////////////////////////////////////////////
//Constructeur

///////////////////////////////////////////////////////////////////////////
Breath::Breath(float _xpos, float _ypos, float _zpos,
               float _size,
               float _xspeed, float _yspeed, float _zspeed,
               float _lifeTime)
    : xpos(_xpos), ypos(_ypos), zpos(_zpos), size(_size),
      xspeed(_xspeed), yspeed(_yspeed), zspeed(_zspeed), lifeTime(_lifeTime)
{}


///////////////////////////////////////////////////////////////////////////
//Destructeur

///////////////////////////////////////////////////////////////////////////
Breath::~Breath()
{}


///////////////////////////////////////////////////////////////////////////
/*Animation de la bouffée de fumée
* timeFrame : temps écoulé entre deux affichages
*/
///////////////////////////////////////////////////////////////////////////
void Breath::anime(float timeFrame)
{
  //Calcul des nouvelles positions
  float newPos[3] = {getxPos() + getxSpeed() * timeFrame,
                     getyPos() + getySpeed() * timeFrame,
                     getzPos() + getzSpeed() * timeFrame};

  //Affectation des nouvelles positions
  setxPos( newPos[0] );
  setyPos( newPos[1] );
  setzPos( newPos[2] );

  //Recalcul du temps de vie
  setLifeTime( getLifeTime() - timeFrame );

  //Taille et transparence

}


///////////////////////////////////////////////////////////////////////////
/*Affichage de la bouffée de fumée
*/
///////////////////////////////////////////////////////////////////////////
void Breath::show()
{
  glDisable(GL_LIGHTING);                             //le quadrilatère de la bouffée n'est pas affecté par la lumière
  glDisable(GL_CULL_FACE);                            //Pour voir les deux côtés de la bouffée
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   //Pour que la couleur de la texture se mélange à celle du reste
  glEnable(GL_BLEND);                                  //de la scène avec des propotions données par l'alpha de chaque texel de la texture

  //Affichage du quadrilatère texturé avec la texture RGBA
  //glBegin(GL_QUADS)
  //...
  //glEnd();

  glDisable(GL_BLEND);
  glEnable(GL_LIGHTING);
  glEnable(GL_CULL_FACE);
}
