//DECOOPMAN Clément

#include <iostream>
#include <math.h>
using namespace std;


#include "Cercle.hpp"



//Constructeur
Cercle::Cercle(float _centreX, float _centreY, float _rayon, unsigned int _nbpoints)
  : centreX(_centreX), centreY(_centreY), rayon(_rayon), nbpoints(_nbpoints), coords(nullptr) //, points(nullptr)
{
  // points = new Point *[nbpoints];   //On ne veut que nbpoints car on trace des lignes entre ces derniers pour former le cercle, inutile d'en faire plus
  coords = new float[nbpoints*3];
  CalcPoints();
}


//Destructeur
Cercle::~Cercle()
{
  // for(size_t i = 0; i < nbpoints; i++)
  //   delete points[i];
  // delete [] points;
  delete [] coords;
}


//Getter des coordonées de tous les points stockés
//renvoie sous forme de tableau les coordonées des points formant le cercle
float *Cercle::getCoords() const
{
  // float *coords = new float[nbpoints*3];   //On a des points en 3 dimensions
  // Point *MonPoint = new Point(0,0);        //Nouveau point pour récupérer les coordonées de ceux stockées
  // unsigned int cpt = 0;                    //Compteur-indice pour stocker les coordonées par paquet de 3 (x,y,z)
  //
  // for(size_t i = 0; i < nbpoints; i++)
  // {
  //   MonPoint       = points[i];
  //   coords[cpt]    = MonPoint->getX();
  //   coords[cpt++]  = MonPoint->getY();
  //   coords[cpt+=2] = 0.0f;
  //   cpt+=3;
  // }
  //
  // delete [] MonPoint;
  return coords;
}


//Calcul des positions des sommets
//d'après l'équation cartésienne du cercle
void Cercle::CalcPoints()
{
	float x = 0.0f;
	float y = 0.0f;
  unsigned int cpt = 0;
	for( size_t angle = 0; angle < 360; angle+=(360/nbpoints) )  //On boucle nbpoints fois au maximum
	{
		x = centreX + rayon * cos(angle);
		y = centreY + rayon * sin(angle);
    coords[cpt]    = x;
    coords[cpt++]  = y;
    coords[cpt+=2] = 0.0f;
    // Point *pts  = new Point(x, y);
    // // points[cpt] = pts;
    //
    // // delete [] pts;
    cpt+=3;
	}
}
