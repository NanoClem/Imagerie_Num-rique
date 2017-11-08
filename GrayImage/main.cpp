#include <iostream>
#include <cstdint>
#include <fstream>

using namespace std;

#include "GrayImage.hpp"



int main()
{

  ifstream chat("chat.pgm", ios::binary);
    GrayImage * lecture = GrayImage::readPGM(chat);

  //lecture -> GrayImage::fillRectangle(35, 65, 150, 200, 255);
  lecture -> GrayImage::rectangle(35, 65, 150, 200, 255);
	
  ofstream chat_modif("chat_modif.pgm", ios::binary);
    lecture -> GrayImage::writePGM(chat_modif);


	
  //Nouvelle image : tester le vide
  // ifstream chat2("chat.pgm", ios::binary);
    // GrayImage * erase = GrayImage::readPGM(chat2);

  // erase -> GrayImage::clear();
  // ofstream vide("vide.pgm", ios::binary);
    // erase -> GrayImage::writePGM(vide);

  return 0;
}
