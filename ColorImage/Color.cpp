
#include "Color.hpp"


Color operator +(const Color& c1, const Color& c2)
{
  uint8_t _r = c1.r + c2.r;     // On ajoute les couleurs
  uint8_t _g = c1.g + c2.g;     // en ajoutant les octets
  uint8_t _b = c1.b + c2.b;     // définissant la couleur entre eux

  return Color(_r, _g, _b);     // variable anonyme retournée
}


Color operator *(double alpha, const Color& color)
{
  uint8_t _r = uint8_t(alpha) * color.r;
  uint8_t _g = uint8_t(alpha) * color.g;
  uint8_t _b = uint8_t(alpha) * color.b;

  return Color(_r, _g, _b);
}
