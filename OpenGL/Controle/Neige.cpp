#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Neige.hpp"



///////////////////////////////////////////////////////////////////////////
/*Constructeur
*/
///////////////////////////////////////////////////////////////////////////
Neige::Neige(float _xmin, float _ymin, float _zmin, float _xmax, float _ymax, float _zmax, list<Flocon>& _floconList,
              float _emissionTime, float _elapsedTime, Texture *_floconTexture)
    : xmin(_xmin), ymin(_ymin), zmin(_zmin), xmax(_xmax), ymax(_ymax), zmax(_zmax), floconList(_floconList), emissionTime(_emissionTime), floconTexture(_floconTexture)
    {}


///////////////////////////////////////////////////////////////////////////
/*Destructeur
*/
///////////////////////////////////////////////////////////////////////////
Neige::~Neige()
{delete [] floconTexture;}



///////////////////////////////////////////////////////////////////////////
/*Charger la texture de la chute de neige
*/
///////////////////////////////////////////////////////////////////////////
void Neige::loadTex()
{
  floconTexture->load((char *)"particule.png");
  floconTexture->define_filter(GL_NEAREST, GL_NEAREST);
  floconTexture->define_melting(GL_MODULATE);
  floconTexture->define_loop(GL_REPEAT, GL_REPEAT);
}



///////////////////////////////////////////////////////////////////////////
/*Animation de la neige
* timeFrame : temps écoulé entre deux étapes d'animation
*/
///////////////////////////////////////////////////////////////////////////
void Neige::anime(float timeFrame)
{
  //Partie 1 : ajout de flocons
  setElapsed(getElapsed() + timeFrame);
  if( getElapsed() > getEmission() )
  {
    //positions aléatoires
    float xrand, yrand, zrand;
    xrand = rand() % int( (getXmax()-getXmin()) + getXmin() );
    xrand = rand() % int( (getYmax()-getYmin()) + getYmin() );
    xrand = rand() % int( (getZmax()-getXmin()) + getXmin() );
    srand(time(NULL));

    setElapsed(0.0f);
    Flocon *flocon = new Flocon(xrand, yrand, zrand, 3.0f, 0.5f, -2.0f, 0.0f, 4.0f);
    floconList.push_back(*flocon);
  }

  //Partie 2 : suppression de flocons
  //on parcours la liste de flocons pour supprimer ceux dont la position est
  //en dessous de ymin
  list<Flocon>::iterator i;
  i = floconList.begin();
  while( i != floconList.end())
  {
    if( i->getxPos() < getYmin() )
      i = floconList.erase(i);
    else
      i++;
  }

  //Partie 3 : calcul des positions
  i = floconList.begin();
  while( i != floconList.end() )
  {
    i->anime(timeFrame);
    i++;
  }
}




///////////////////////////////////////////////////////////////////////////
/*Affichage de la neige
*/
///////////////////////////////////////////////////////////////////////////
void Neige::show()
{
    glDepthMask(GL_FALSE);
    list<Flocon>::iterator i = floconList.begin();
    while( i != floconList.end() )
    {
      i->show();
      i++;
    }
    glDepthMask(GL_TRUE);
}
