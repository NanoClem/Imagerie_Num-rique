//DECOOPMAN Clément & DAMIENS Lucas
//Dans le cadre du projet final C++ Info1

#include <iostream>
using namespace std;

#include "Point.hpp"


//Constructeur
Point::Point(float _x, float _y)
	: x(_x), y(_y)
	{}


//Destructeur
Point::~Point()
	{}


//Constructeur par copie
Point::Point(const Point& origine)
	: Point(origine.x, origine.y)
	{}


//Flux d'entree
Point::Point(istream& is)
	: x(0), y(0)
	{is >> x >> y;}


// //Observateur
// bool Point::isOver(float _x, float _y) const
// {
// 	float dx, dy;
// 	dx = (x<_x?_x-x:x-_x); 		//operateur ternaire, empeche x d'etre negatif
// 	dy = (y<_y?_y-y:y-_y);
//
// 	return (dx<=taille && dy<=taille);
// }


//Operateur de sortie
ostream& operator <<(ostream& os, const Point p)
{
	os << p.x << " " << p.y;
	return os;
}


//Operateur d'entree
istream& operator >>(istream& is, Point &p)
{
	is >> p.x >> p.y;
	return is;
}


//Operateur =
Point& Point::operator =(const Point &src)
{
	x = src.x;
	y = src.y;

	return *this;
}
