#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Vector3f.hpp"
#include "Flocon.hpp"



//Constructeur
Flocon::Flocon(float _xpos, float _ypos, float _zpos,
               float _size,
               float _xspeed, float _yspeed, float _zspeed,
               float _lifeTime)
    : xpos(_xpos), ypos(_ypos), zpos(_zpos), size(_size),
      xspeed(_xspeed), yspeed(_yspeed), zspeed(_zspeed), lifeTime(_lifeTime)
{maxLifeTime = lifeTime;}



//Destructeur
Flocon::~Flocon()
{}



  ///////////////////////////////////////////////////////////////////////////
  /*Animation du flocon
  * timeFrame : temps écoulé entre deux affichages
  */
  ///////////////////////////////////////////////////////////////////////////
void Flocon::anime(float timeFrame)
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
  setSize( getSize() + getLifeTime()/50.0f );
}




///////////////////////////////////////////////////////////////////////////
/*Affichage du flocon
*/
///////////////////////////////////////////////////////////////////////////
void Flocon::show()
{
  glDisable(GL_LIGHTING);                              //le quadrilatère de la bouffée n'est pas affecté par la lumière
  glDisable(GL_CULL_FACE);                             //Pour voir les deux côtés de la bouffée
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   //Pour que la couleur de la texture se mélange à celle du reste
  glEnable(GL_BLEND);                                  //de la scène avec des propotions données par l'alpha de chaque texel de la texture

  //Billboarding : orienter le quadrilatère toujours vers la caméra
    //Récupération des coords de la caméra
    float matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

    Vector3f top, right;
    right.x = matrix[0] * ( getSize()/2.0f );
    right.y = matrix[4] * ( getSize()/2.0f );
    right.z = matrix[8] * ( getSize()/2.0f );
    top.x   = matrix[1] * ( getSize()/2.0f );
    top.y   = matrix[5] * ( getSize()/2.0f );
    top.z   = matrix[9] * ( getSize()/2.0f );

    //Calcul de la pos des 4 sommets du quadrilatère
    Vector3f A, B, C, D;
    A.x = getxPos() + top.x - right.x;    B.x = getxPos() + top.x + right.x;
    A.y = getyPos() + top.y - right.y;    B.y = getyPos() + top.y + right.y;
    A.z = getzPos() + top.z - right.z;    B.z = getzPos() + top.z + right.z;

    C.x = getxPos() - top.x + right.x;    D.x = getxPos() - top.x - right.x;
    C.y = getyPos() - top.y + right.y;    D.y = getyPos() - top.y - right.y;
    C.z = getzPos() - top.z + right.z;    D.z = getzPos() - top.z - right.z;


  //Affichage du quadrilatère texturé avec la texture RGBA
  glColor4f(0.5f, 0.5f, 0.5f, lifeTime/maxLifeTime);
  glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f);
    glVertex3f(D.x,D.y,D.z);
      glTexCoord2f(0.0f, 1.0f);
    glVertex3f(C.x,C.y,C.z);
      glTexCoord2f(1.0f, 1.0f);
    glVertex3f(B.x,B.y,B.z);
      glTexCoord2f(1.0f, 0.0f);
    glVertex3f(A.x,A.y,A.z);
  glEnd();

  glDisable(GL_BLEND);
  glEnable(GL_LIGHTING);
  glEnable(GL_CULL_FACE);
}
