// Classe Image


const char * const identifier   = "decoopman_c";

const char * const informations =
"METTRE DES COMMENTAIRES \n"
"correspond aux infos supplémentaires du programme pour le correcteur"
;



// CLASSE COLOR :
// instancier le modèle RGB pour définir la couleur de chaque pixel
// sur 3 octets successifs donnant les valeurs respectives
// du rouge, vert et bleu



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









// Classe ColorImage



#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdexcept>

using namespace std;


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
		static ColorImage * readTGA(istream& is);
		void writeTGA(ostream& os, bool rle=true) const;
		static ColorImage * readMaison2(istream& is);
		void writeMaison2(ostream& os) const;


		ColorImage * anaglyphe() const;
    ColorImage * simpleScale(uint16_t w, uint16_t h) const;
		ColorImage * bilinearScale(uint16_t w, uint16_t h) const;


		friend void skip_line(istream& is);
		friend void skip_comment(istream& is);

};






// Classe GrayImage


#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdexcept>

using namespace std;



class GrayImage {

	private :

		const uint16_t width, height;
		uint8_t * array;



	public :

		GrayImage() = delete;
		GrayImage(const GrayImage& src);
		~GrayImage();
		GrayImage(uint16_t w, uint16_t h);


		static GrayImage * readPGM(istream& is);
		void writePGM(ostream& os) const;
		GrayImage * simpleScale(uint16_t w, uint16_t h) const;
		GrayImage * bilinearScale(uint16_t w, uint16_t h) const;



		//Getters et Setters
		inline const uint16_t& getWidth() const  {return width;}
		inline const uint16_t& getHeight() const {return height;}

		inline uint8_t& pixel(uint16_t x, uint16_t y) {return array[y*width+x];}								//Getter de modification
		inline const uint8_t& pixel(uint16_t x, uint16_t y) const {return array[y*width+x];}		//Getter de consultation


		//Operator
		GrayImage& operator =(const GrayImage& b) = delete;


		void clear(uint8_t color=00);
		void rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);
		void fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);


		friend void skip_line(istream& is);
		friend void skip_comment(istream& is);
};
