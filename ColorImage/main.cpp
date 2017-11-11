#include <iostream>
#include <cstdint>
#include <fstream>

using namespace std;

#include "ColorImage.hpp"




//SAVOIR SI ON EST EN BIG-ENDIAN OU LITLE-ENDIAN
bool * BigOrLitle()
{
  bool * isEndian = new bool();
  uint16_t toto = 0x00FF;
  uint8_t * ptr = (uint8_t *)&toto;

  if(*ptr == 0xFF)
  {
    cout << "LITLE-ENDIAN \n";
    *isEndian = true;
    return isEndian;
  }

  if(*ptr == 0x00)
  {
    cout << "BIG-ENDIAN \n";
    *isEndian = false;
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
  uint16_t w = 823;
  uint16_t h = 400;

//LECTURE DE L'IMAGE DE BASE
  ifstream chat("chat.ppm", ios::binary);
    ColorImage * chat1 = ColorImage::readPPM(chat);

//MODIFICATIONS DE L'IMAGE : dessins de rectangles
  chat1 -> ColorImage::fillRectangle(35, 65, 150, 200, color);
  chat1 -> ColorImage::rectangle(165, 65, 290, 200, color);

//ECRITURE DE L'IMAGE MODIFIÉE N°1
  ofstream chat_modif("chat_modif.ppm", ios::binary);
    chat1 -> ColorImage::writePPM(chat_modif);


//LECTURE D'UNE NOUVELLE IMAGE DE BASE
  ifstream chat_petit("chat_petit.ppm", ios::binary);
    ColorImage * chat2 = ColorImage::readPPM(chat_petit);

//MODIFICATIONS DE LA NOUVELLE IMAGE : réchantillonage simpliste (823x400)
  chat2 -> ColorImage::simpleScale(w, h);

//ECRITURE DE L'IMAGE MODIFIÉE N°2
  ofstream chat_grand_simple("chat_grand_simple.ppm", ios::binary);
    chat2 -> ColorImage::writePPM(chat_grand_simple);


//AFFICHER LES VALEURS PRISES PAR CHACUN DES 3 OCTETS D'UN PIXEL DONNÉ
   Color temp = chat1 -> pixel(50,20);
   cout << "Color used : " << temp << endl;



  //REMPLISSAGE OU "VIDAGE" DE L'IMAGE DE BASE
  ifstream chat_base("chat.ppm", ios::binary);
    ColorImage * erase = ColorImage::readPPM(chat_base);
  erase -> ColorImage::clear(color);

  //ECRITURE DE L'IMAGE REMPLIE OU VIDÉE
  ofstream vide("chat_vide.ppm", ios::binary);
    erase -> ColorImage::writePPM(vide);

  return 0;
}
