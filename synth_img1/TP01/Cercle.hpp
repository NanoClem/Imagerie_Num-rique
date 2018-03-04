//DECOOPMAN Clément


#ifndef CERCLE_HPP
#define CERCLE_HPP

#include <iostream>
using namespace std;

#include "Point.hpp"


class Cercle {

	static const unsigned int nbpoints = 9;

	private:

		float centreX, centreY, rayon;
		Point **points;


	public:

		Cercle(float _centreX, float _centreY, float _rayon);
		~Cercle();
		void CalcPoints();

		inline float getRayon()    const 		{return rayon;}
		inline float getCentreX()	 const		{return centreX;}
		inline float getCentreY()  const		{return centreY;}
		inline Point **getPoints() const 		{return points;}		//Récupérer l'ensemble des points
		float *getCoords()				 const;											  //Récupérer les coordonées de tous les points sous un seul tableau

		inline void setRayon(float _rayon)  			{rayon = _rayon;}
		inline void setCentreX(float _centreX)		{centreX = _centreX;}
		inline void setCentreY(float _centreY)		{centreY = _centreY;}
};

#endif
