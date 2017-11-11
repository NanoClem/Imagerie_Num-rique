#include <iostream>
#include <cstdint>
#include <fstream>

using namespace std;

#include "GrayImage.hpp"



int main()
{
  uint16_t w = 823;   //nouvelle longueur pour le réchantillonage
  uint16_t h = 400;


  //LECTURE DE L'IMAGE DE BASE : chat.ppm
    ifstream cat("chat.pgm", ios::binary);
      GrayImage * cat1 = GrayImage::readPGM(cat);

  //MODIFICATIONS DE L'IMAGE : dessins de rectangles
    cat1 -> GrayImage::fillRectangle(35, 65, 150, 200, 255);
    cat1 -> GrayImage::rectangle(165, 65, 290, 200, 255);

  //ECRITURE DE L'IMAGE MODIFIÉE N°1 : squared_head_cat.pgm
    ofstream squared_cat("squared_head_cat.pgm", ios::binary);
      cat1 -> GrayImage::writePGM(squared_cat);



  //LECTURE D'UNE NOUVELLE IMAGE DE BASE : chat_petit.pgm
    ifstream little_cat("chat_petit.pgm", ios::binary);
      GrayImage * cat2 = GrayImage::readPGM(little_cat);

  //MODIFICATIONS DE L'IMAGE chat_petit.pgm : réchantillonage simpliste (823x400)
    GrayImage * simple_cat = cat2 -> GrayImage::simpleScale(w, h);
    //cat2 = cat2 -> GrayImage::simpleScale(w, h);  //On pert l'image pointée par cat2 à la base

  //ECRITURE DE L'IMAGE MODIFIÉE : big_jammed_cat.pgm
    ofstream big_simple_cat("big_jammed_cat.pgm", ios::binary);
      simple_cat -> GrayImage::writePGM(big_simple_cat);
      //cat2 -> GrayImage::writePGM(big_simple_cat);



  //MODIFICATIONS DE L'IMAGE chat_petit.pgm  : réchantillonage bilinéaire (823x400)
    GrayImage * bilinear_cat = cat2 -> GrayImage::bilinearScale(w, h);

  //ECRITURE DE L'IMAGE MODIFIÉE : big_blurred_cat.pgm
    ofstream big_bilinear_cat("big_blurred_cat.pgm", ios::binary);
      bilinear_cat -> GrayImage::writePGM(big_bilinear_cat);
      //cat2 -> GrayImage::writePPM(big_bilinear_cat);



  //NOUVELLE IMAGE : "vider" l'image
    ifstream chat2("chat.pgm", ios::binary);
      GrayImage * erase = GrayImage::readPGM(chat2);

    erase -> GrayImage::clear();
      ofstream vide("chat_vide.pgm", ios::binary);
      erase -> GrayImage::writePGM(vide);

  return 0;
}
