#include <iostream>
#include <cstdint>
#include <fstream>

using namespace std;

#include "GrayImage.hpp"



int main()
{

  ifstream chat("chat.pgm", ios::binary);
    GrayImage * lecture = GrayImage::readPGM(chat);

  lecture -> GrayImage::fillRectangle(35, 65, 150, 200, 255);
  lecture -> GrayImage::rectangle(165, 65, 290, 200, 255);
	
  ofstream chat_modif("chat_modif.pgm", ios::binary);
    lecture -> GrayImage::writePGM(chat_modif);


	
  //NOUVELLE IMAGE : "vider" l'image
  
  ifstream chat2("chat.pgm", ios::binary);
    GrayImage * erase = GrayImage::readPGM(chat2);

  erase -> GrayImage::clear();
    ofstream vide("chat_vide.pgm", ios::binary);
    erase -> GrayImage::writePGM(vide);

  return 0;
}
