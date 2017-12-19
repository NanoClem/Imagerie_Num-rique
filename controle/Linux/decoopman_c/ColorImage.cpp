// Définition des fonctions de la classe ColorImage

#include "ColorImage.hpp"


//Constructeur
ColorImage::ColorImage(uint16_t w, uint16_t h)
	: width(w), height(h), array(nullptr)
{ array = new Color [width*height]; }




//Destructeur
ColorImage::~ColorImage()
{ delete [] array; }




//Construct Copie
ColorImage::ColorImage(const ColorImage& src)
	:width(src.width), height(src.height), array(nullptr)
{
	array = new Color [src.width*src.height];

	for(size_t t=0; t < size_t(src.width*src.height); t++)
	  array[t] = src.array[t];
}




void skip_line(istream& is)
{
	char c;

	do{
		is.get(c);
	}
	while(c!='\n');
}




void skip_comments(istream& is)
{
	char c;
	is.get(c);

	while(c=='#')
	{
		skip_line(is);
		is.get(c);
	}

	is.putback(c);
}




void ColorImage::writePPM(ostream& os) const {

	os << "P6\n"
	   << "#image sauvee par D.Clement\n"
	   << width << " " << height << "\n"
	   <<  "#GPALU\n"
	   << "255\n";

	//for(size_t i=0; i<size_t(width*height); i++)
		//os.put(array[i]);

	os.write((const char *)array, width*height*3);  //La couleur est sur 3 octets donc 3x plus
}





ColorImage * ColorImage::readPPM(istream& is)
{
	string c;
	is >> c;
  //getline(is, c);  //Consomme le "\n"   => Erreur : empêche la lecture de "P6"

	if(c != "P6")
		throw runtime_error("Error : not a PPM !");

	skip_line(is);
	skip_comments(is);

	uint16_t width, height;
	is >> width >> height;
  is.get();    //Saute le "\n" après height

	//skip_line(is);    => Erreur : Saute la precision
	skip_comments(is);

	uint16_t maxpixel;
	is >> maxpixel;

	if(maxpixel != 255)
		throw runtime_error("Erreur : précision max dépassée");

  //is.get();     //D'après la doc, il y a un "\n"    => Erreur : les couleurs ne sont pas affichées correctement
	skip_line(is);

	ColorImage * picture = new ColorImage(width, height);
	is.read((char *)picture->array,width*height*3);

	return picture;
}





// void ColorImage::writeTGA(ostream& os) const
// {
// 	os << "0";
// 	os.write((const char *));
// }
//
//
//
//
//
// ColorImage * ColorImage::readTGA(istream& is)
// {
//
// }





void ColorImage::clear(Color color)
{
	for(size_t i=0; i<size_t(getWidth() * getHeight()); ++i)
		array[i] = color;
}





void ColorImage::rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color)
{
	if(w >= getWidth() || h >= getHeight())
		cerr << "RECTANGLE(), dimensions invalides \n";

	else if( (x <= 0) && (y <= 0) )
		cerr << "RECTANGLE(), les coordonnées de depart n'existent pas dans l'image \n";

	else
	{
		for(uint16_t _x = x; _x < w; ++_x)
		{
			pixel(_x, y) = color;
			pixel(_x, h) = color;
		}

		for(uint16_t _y = y; _y < h; ++_y)
		{
			pixel(x, _y) = color;
			pixel(w, _y) = color;
		}
	}
}



void ColorImage::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color)
{
	if(w >= getWidth() || h >= getHeight())
		cerr << "FILLRRECTANGLE(), dimensions invalides \n";

	else if( (x <= 0) || (y <= 0) )
		cerr << "FILLRECTANGLE(), les coordonnées de depart n'existent pas dans l'image \n";

	else
	{
		for(size_t _x = x; _x < size_t(w); ++_x)
			for(size_t _y = y; _y < size_t(h); ++_y)
				pixel(_x, _y) = color;
	}
}



ColorImage * ColorImage::simpleScale(uint16_t w, uint16_t h) const
{
  ColorImage * picture = new ColorImage(w, h);

  for(uint16_t _y = 0; _y < h; ++_y)
    for(uint16_t _x = 0; _x < w; ++_x)
    {
      uint16_t xi = uint16_t( double(_x)*getWidth() / w );
      uint16_t yi = uint16_t( double(_y)*getHeight() / h );

      picture -> pixel(_x, _y) = pixel(xi, yi);
    }

    return picture;
}




ColorImage * ColorImage::bilinearScale(uint16_t w, uint16_t h) const
{
	ColorImage * picture = new ColorImage(w, h);

	for(uint16_t _y = 0; _y < h; ++_y)
		for(uint16_t _x = 0; _x < w; ++_x)
		{
			double x = double(_x * getWidth())  / w;
			double y = double(_y * getHeight()) / h;

			uint16_t xi = uint16_t(x);
			uint16_t yi = uint16_t(y);

			uint16_t x2 = (xi+1 < getWidth()  ? xi+1 : xi);		//Si xi+1 < width on prend xi+1 sinon xi
			uint16_t y2 = (yi+1 < getHeight() ? yi+1 : yi);		//Au cas où on dépasse les dimensions de l'image

			double lambda = x-xi;
			double mu     = y-yi;

			picture -> pixel(_x, _y) = (1-lambda) * ((1-mu)*pixel(xi,yi) + mu*pixel(xi,y2))
				                       +     lambda * ((1-mu)*pixel(x2,yi) + mu*pixel(x2,y2));
		}

	return picture;
}
