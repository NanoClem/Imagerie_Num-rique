#include <iostream>
#include <cstdint>
#include <fstream>

using namespace std;

#include "GrayImage.hpp"



int main()
{

  ifstream chat("chat.pgm", ios::binary);
    GrayImage * lecture = GrayImage::readPGM(chat);

  ofstream chat_modif("chat_modif.pgm", ios::binary);
    lecture -> GrayImage::writePGM(chat_modif);


  //Nouvelle image : tester le vide
  ifstream chat2("chat.pgm", ios::binary);
    GrayImage * erase = GrayImage::readPGM(chat2);


  erase -> GrayImage::clear();
  erase -> GrayImage::rectangle(100, 50, erase -> getWidth(), erase -> getHeight(), 255);
  //erase -> GrayImage::fillRectangle(10, 5, erase -> getWidth(), erase -> getHeight(), 255);
  ofstream vide("rectangle.pgm", ios::binary);
    erase -> GrayImage::writePGM(vide);

    //préciser les couleurs

  return 0;
}
