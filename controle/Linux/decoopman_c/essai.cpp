#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

/*
 Toutes vos définitions de classes doivent être regroupées dans l'unique
 fichier "Image.h". Son nom n'est pas modifiable sinon vous empêcherez la
 compilation de l'autre executable servant à la correction.
*/
#include "Image.hpp"

extern const char * const identifier;   // Ne pas modifier ces deux lignes ! Vos changements au sujet
extern const char * const informations; // de ceux deux constantes doivent être faits dans Image.cpp.


int main(int argc,char *argv[])
{
 cout << "Votre identifiant tel que declare dans Image.cpp : " << identifier << endl;
 cout << "Les informations que vous avez decide d'indiquer au correcteur : " << endl << informations << endl;
 try
  {
    // Color color(0,120,255);   //nouvelle couleur de pixel
    // uint16_t w = 823;         //nouvelle longueur pour le réchantillonage
    // uint16_t h = 400;
    // uint16_t temp_x = 50;     //variable temp pour la consultation de couleur d'un pixel de l'image
    // uint16_t temp_y = 20;


  //LECTURE DE L'IMAGE DE BASE : chat.ppm
    ifstream shadow_test("ombres.ppm", ios::binary);
      ColorImage * shadow = ColorImage::readPPM(shadow_test);

  //MODIFICATION EN ANAGLYPHE
      shadow -> ColorImage::anaglyphe();

      ofstream d3_shadow("3D_ombres.ppm", ios::binary);
        shadow -> ColorImage::writePPM(d3_shadow);


  //ECRITURE DE L'IMAGE MODIFIÉE N°1 : squared_head_cat.ppm
    // ofstream copy_cat("copy_cat.ppm", ios::binary);
    //   cat1 -> ColorImage::writeMaison2(copy_cat);

  } // Trois types d'exceptions seront attrapés (les chaines C et C++ ainsi que
    // les std::exception et toutes ses dérivées). N'utilisez pas autre chose !
 catch(exception& e)
  { cerr<< "Exception :"<<e.what()<< endl; }
 catch(string& e)
  { cerr<< "Exception string :"<<e<< endl; }
 catch(const char * e)
  { cerr<< "Exception const char* :"<<e<< endl; }
 return 0;
}
