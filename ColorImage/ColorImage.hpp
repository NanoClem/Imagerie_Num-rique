// Classe ColorImage

#ifndef COLORIMAGE_HPP
#define COLORIMAGE_HPP

#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdexcept>

using namespace std;

#include "Color.hpp"



class ColorImage {

	private :

		uint16_t width, height;
		Color * array;



	public :

		ColorImage() = delete;
		ColorImage(const ColorImage& src);
		~ColorImage();
		ColorImage(uint16_t w, uint16_t h);


		//Getters et Setters
		inline const uint16_t& getWidth() const  {return width;}
		inline const uint16_t& getHeight() const {return height;}

		inline Color& pixel(uint16_t x, uint16_t y) {return array[y*width+x];}								//Getter de modification
		inline const Color& pixel(uint16_t x, uint16_t y) const {return array[y*width+x];}		//Getter de consultation


		//Operator
		ColorImage& operator =(const ColorImage& b) = delete;


		void clear(Color color=00);
		void rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color);
		void fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color);

    static ColorImage * readPPM(istream& is);
    void writePPM(ostream& os) const;
    ColorImage * simpleScale(uint16_t w, uint16_t h) const;

		friend void skip_line(istream& is);
		friend void skip_comment(istream& is);

};

#endif
