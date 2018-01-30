#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Smoke.hpp"


///////////////////////////////////////////////////////////////////////////
/*Constructeur
*/
///////////////////////////////////////////////////////////////////////////
Smoke::Smoke(float _x, float _y, float _z, list<Breath>& _breathList,
             float _emissionTime, float _elapsedTime, Texture& _breathTexture)
    : x(_x), y(_y), z(_z), breathList(_breathList), emissionTime(_emissionTime), breathTexture(_breathTexture)
{}


///////////////////////////////////////////////////////////////////////////
/*Destructeur
*/
///////////////////////////////////////////////////////////////////////////
Smoke::~Smoke()
{delete [] breathTexture;}


///////////////////////////////////////////////////////////////////////////
/*Animation de la fumée
* timeFrame : temps écoulé entre deux étapes d'animation
*/
///////////////////////////////////////////////////////////////////////////
void Smoke::anime(float timeFrame)
{
  //Partie 1 : ajout de bouffées
  setElapsed(getElapsed() + timeFrame);
  if( getElapsed() > getEmission() )
  {
    setElapsed(0.0f);
    Breath *breath = new Breath(getX(), getY(), getZ(), 10.0f, 3.0f, 3.0f, 3.0f, 5.0f);
    breathList.push_back(breath);
  }

  //Partie 2 : suppression de bouffées
  //on parcours la liste de bouffées pour supprimer celles dont la durée
  //de vie s'est écoulée
  list<Breath>::iterator i;
  i = breathList.begin();
  while( i != breathList.end())
  {
    if( i->getLifeTime() <= 0 )
      i = breathList.erase(i);
    else
      i++;
  }

  //Partie 3 : calcul des positions
  while( i != breathList.end() )
  {
    i->anime(timeFrame);
    i++;
  }
}


///////////////////////////////////////////////////////////////////////////
/*Affichage de la fumée
*/
///////////////////////////////////////////////////////////////////////////
void Smoke::show()
{
  
}
