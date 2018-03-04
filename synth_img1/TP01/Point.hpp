
/// \author Lucas.D & Clement.D
/// \brief dans le cadre du projet final C++ info1


#ifndef POINT_HPP
#define POINT_HPP


/** \class Point
	\brief classe permettant de modéliser un point en 2 dimensions
*/
class Point {

	private :
		float x, y;						///< coordonnés du point

	public :
		/** \brief Constructeur
			Constructeur de la classe Point
			\param x : abscisse du point
			\param y : ordonnée du point
		*/
		Point(float x, float y);

		/** \brief Destructeur
			Destructeur de la classe Point
		*/
		~Point();

		/** \brief Constructeur de copie
			Constructeur par recopie de la classe Point
			\param origine : référence constante de type Point pour la recopie des paramètres du constructeur
		*/
		Point(const Point& origine);

		/** \brief Flux d'entrée
			Flux d'entrée de la classe Point
			\param is : référence de type istream pour passer en entrée les instances de Point
		*/
		Point(istream& is);

		/** \brief Setter des coordonnés
			Setter pour modifier la valeur de l'abscisse et l'ordonnée du point
			\param _x : entier non signé pour modifier la valeur de l'abscisse
			\param _y ! entier non signé pour modifier la valeur de l'ordonnée
		*/
		inline void setXY(float _x, float _y) {x=_x; y=_y;}

		/** \brief Observateur de la classe Point
			Observateur permettant de vérifier si la position de la souris se trouve au dessus de l'ancre
			\param x : abscisse du curseur de la souris
			\param y : ordonnée du curseur de la souris
		*/
		// bool isOver(float x, float y) const;

		/** \brief opérator de sortie de la classe Point
			Surchage de l'opérateur de sortie pour la classe Point
			\param os : référence de type ostream pour diriger les instances de Forme vers le flux de sortie
			\param p : référence constante de type Point pour accéder aux instances de la classe Point
		*/
		friend ostream& operator <<(ostream& os, const Point p);

		/** \brief opérator d'entrée de la classe Point
			Surchage de l'opérateur d'entrée pour la classe Forme
			\param is : référence de type istream pour passer en entrée les instances de Point
			\param p : référence constante de type Point pour accéder aux instances de la classe Point
		*/
		friend istream& operator >>(istream& is, Point& p);

		/** \brief opérator d'affectation de la classe Point
			Surchage de l'opérateur d'affectation pour la classe Forme
			\param src : référence constante de type Point pour accéder aux instances de la classe Point
		*/
		Point& operator =(const Point &src);

		/** \brief Getter constant de l'abscisse
			Getter pour obtenir la valeur courrante de l'abscisse du point
		*/
		inline float getX() const {return x;}

		/** \brief Getter constant de l'ordonnée
			Getter pour obtenir la valeur courrante de l'ordonnée du point
		*/
		inline float getY() const {return y;}
};

#endif
