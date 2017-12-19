// CLASSE COLOR :
// instancier le modèle RGB pour définir la couleur de chaque pixel
// sur 3 octets successifs donnant les valeurs respectives
// du rouge, vert et bleu


#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>
#include <iostream>
//#include <stdexcept>

using namespace std;



class Color {

  public :

    uint8_t r, g, b;

    inline Color(uint8_t _r=0, uint8_t _g=0, uint8_t _b=0)
      : r(_r), g(_g), b(_b)
      {/*cerr << "Modèle RGB \n";*/}

    inline ~Color()
      {/*cerr << "Destruction de RGB \n";*/}


    inline void printColor(ostream& os) const
      {os << uint16_t(r) << " " << uint16_t(g) << " " << uint16_t(b) << endl;}

  //Opérateurs
    friend Color operator*(double alpha, const Color& color);
    friend Color operator+(const Color& c1, const Color& c2);
    inline friend ostream& operator<<(ostream& os, const Color& color)
      {color.printColor(os); return os;}


    //autres fonctions de conversion
};

#endif
