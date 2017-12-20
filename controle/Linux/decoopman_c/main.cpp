#include <iostream>
#include <cstdint>
#include <fstream>

using namespace std;

#include "ColorImage.hpp"




//SAVOIR SI ON EST EN BIG-ENDIAN OU LITLE-ENDIAN
bool * BigOrLitle()   //Fonction bool si l'on veut faire une action en fonction du retour
{
  bool * isEndian = new bool();
  uint16_t toto = 0x00FF;
  uint8_t * ptr = (uint8_t *)&toto;

  if(*ptr == 0xFF)
  {
    cout << "LITLE-ENDIAN \n";
    (*isEndian) = true;
    return isEndian;
  }

  if(*ptr == 0x00)
  {
    cout << "BIG-ENDIAN \n";
    (*isEndian) = false;
    return isEndian;
  }

  else
  {
    cout << "ANOTHER ENDIAN \n";
    return(NULL);
  }
}




int main()
{
  //CONNAÎTRE L'ENDIANESS
    // bool * Endianess = new bool();
    // Endianess = BigOrLitle();
    // cout << (*Endianess) << endl;
    // delete [] Endianess;

  Color color(0,120,255);   //nouvelle couleur de pixel
  uint16_t w = 823;         //nouvelle longueur pour le réchantillonage
  uint16_t h = 400;
  uint16_t temp_x = 50;     //variable temp pour la consultation de couleur d'un pixel de l'image
  uint16_t temp_y = 20;


//LECTURE DE L'IMAGE DE BASE : chat.ppm
  ifstream cat("chat.ppm", ios::binary);
    ColorImage * cat1 = ColorImage::readPPM(cat);

//MODIFICATIONS DE L'IMAGE : dessins de rectangles
  cat1 -> ColorImage::fillRectangle(35, 65, 150, 200, color);
  cat1 -> ColorImage::rectangle(165, 65, 290, 200, color);

//ECRITURE DE L'IMAGE MODIFIÉE N°1 : squared_head_cat.ppm
  ofstream squared_cat("squared_head_cat.ppm", ios::binary);
    cat1 -> ColorImage::writePPM(squared_cat);



//LECTURE D'UNE NOUVELLE IMAGE DE BASE : chat_petit.ppm
  ifstream little_cat("chat_petit.ppm", ios::binary);
    ColorImage * cat2 = ColorImage::readPPM(little_cat);

//MODIFICATIONS DE L'IMAGE chat_petit.ppm : réchantillonage simpliste (823x400)
  ColorImage * simple_cat = cat2 -> ColorImage::simpleScale(w, h);
  //cat2 = cat2 -> ColorImage::simpleScale(w, h);  //On pert l'image pointée par cat2 à la base

//ECRITURE DE L'IMAGE MODIFIÉE : big_jammed_cat.ppm
  ofstream big_simple_cat("big_jammed_cat.ppm", ios::binary);
    simple_cat -> ColorImage::writePPM(big_simple_cat);
    //cat2 -> ColorImage::writePPM(big_simple_cat);



//MODIFICATIONS DE L'IMAGE chat_petit.ppm  : réchantillonage bilinéaire (823x400)
  ColorImage * bilinear_cat = cat2 -> ColorImage::bilinearScale(w, h);

//ECRITURE DE L'IMAGE MODIFIÉE : big_blurred_cat.ppm
  ofstream big_bilinear_cat("big_blurred_cat.ppm", ios::binary);
    bilinear_cat -> ColorImage::writePPM(big_bilinear_cat);
    //cat2 -> ColorImage::writePPM(big_bilinear_cat);



//REMPLISSAGE OU "VIDAGE" DE L'IMAGE DE BASE
  ifstream basic_cat("chat.ppm", ios::binary);
    ColorImage * erase = ColorImage::readPPM(basic_cat);
  erase -> ColorImage::clear(color);

//ECRITURE DE L'IMAGE REMPLIE OU VIDÉE
  ofstream vide("cat_vide.ppm", ios::binary);
    erase -> ColorImage::writePPM(vide);



//AFFICHER LES VALEURS PRISES PAR CHACUN DES 3 OCTETS D'UN PIXEL DONNÉ
   Color temp = cat1 -> pixel(temp_x, temp_y);
   cout << "Color used for chat.ppm at " << "(" << temp_x << ", " << temp_y <<") : " << temp << endl;


  return 0;
}
