//DECOOPMAN Clément

#include <iostream>
#include <math.h>
using namespace std;


#include "Cercle.hpp"



//Constructeur
Cercle::Cercle(float _centreX, float _centreY, float _rayon)
  : centreX(_centreX), centreY(_centreY), rayon(_rayon)
{
  points = new Point *[nbpoints];   //On ne veut que nbpoints car on trace des lignes entre ces derniers pour former le cercle, inutile d'en faire plus
  CalcPoints();
}


//Destructeur
Cercle::~Cercle()
{
  for(size_t i = 0; i < nbpoints; i++)
    delete points[i];
  delete [] points;
}


//Getter des coordonées de tous les points stockés
//
float *Cercle::getCoords() const
{
  float *coords = new float[nbpoints*3];   //On a des points en 3 dimensions

  for(size_t i = 0; i < nbpoints; i++)
  {
    Point *MonPoint = points[i];
    coords[i] = MonPoint->getX();
    coords[i++] = MonPoint->getY();
    coords[i+=2] = 0.0f;

    delete [] MonPoint;
  }

  return coords;
}


//Calcul des positions des sommets
//d'après l'équation cartésienne du cercle
void Cercle::CalcPoints()
{
	float x = 0.0f;
	float y = 0.0f;
  size_t cpt = 0;
	for( size_t angle = 0; angle < 360; angle+=(360/nbpoints) )  //On boucle nbpoints fois au maximum
	{
		x = centreX + rayon * cos(angle);
		y = centreY + rayon * sin(angle);
    Point *pts = new Point(x, y);
    points[cpt] = pts;

    delete [] pts;
    cpt++;
	}
}
