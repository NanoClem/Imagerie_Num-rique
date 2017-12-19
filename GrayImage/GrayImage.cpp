// Définition des fonctions de la classe GrayImage

#include "GrayImage.hpp"


//Constructeur
GrayImage::GrayImage(uint16_t w, uint16_t h)
	:width(w), height(h), array(nullptr)
{ array = new uint8_t [width*height]; }




//Destructeur
GrayImage::~GrayImage()
{ delete [] array; }




//Construct Copie
GrayImage::GrayImage(const GrayImage& src)
	:width(src.width), height(src.height), array(nullptr)

{ 	array = new uint8_t [src.width*src.height];

  	for(size_t t=0; t < size_t(src.width*src.height); t++)
			array[t] = src.array[t];
}





void GrayImage::writePGM(ostream& os) const {

	os << "P5\n"
	   << "#image sauvee par D.Clement\n"
	   << width << " " << height << "\n"
	   <<  "#GPALU\n"
	   << "255\n";

	//for(size_t i=0; i<size_t(width*height); i++)
		//os.put(array[i]);

	os.write((const char *)array, width*height);
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




GrayImage * GrayImage::readPGM(istream& is)
{
	string c;
	is >> c;

	if(c!="P5")
		throw runtime_error("Erreur : pas un PGM !");

	skip_line(is);
	skip_comments(is);

	uint16_t width, height;
	is >> width >> height;

	skip_line(is);
	skip_comments(is);

	uint16_t nu_grey;
	is >> nu_grey;

	if(nu_grey!=255)
		throw runtime_error("Erreur : nuance de gris != 255");

	skip_line(is);

	GrayImage *picture = new GrayImage(width, height);
	is.read((char *)picture->array,width*height);

	return picture;
}





void GrayImage::clear(uint8_t color)
{
	for(size_t i=0; i<size_t(getWidth() * getHeight()); ++i)
		array[i] = color;
}





void GrayImage::rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color)
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




void GrayImage::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color)
{
	if(w >= getWidth() || h >= getHeight())
		cerr << "FILLRRECTANGLE(), dimensions invalides \n";

	else if( (x <= 0) || (y <= 0) )
		cerr << "FILLRRECTANGLE(), les coordonnées de depart n'existent pas dans l'image \n";

	else
	{
		for(size_t _x = x; _x < size_t(w); ++_x)
			for(size_t _y = y; _y < size_t(h); ++_y)
				pixel(_x, _y) = color;
	}
}




GrayImage * GrayImage::simpleScale(uint16_t w, uint16_t h) const
{
  GrayImage * picture = new GrayImage(w, h);

  for(uint16_t _y = 0; _y < h; ++_y)
    for(uint16_t _x = 0; _x < w; ++_x)
    {
      uint16_t xi = uint16_t( double(_x)*getWidth() / w );
      uint16_t yi = uint16_t( double(_y)*getHeight() / h );
      picture -> pixel(_x, _y) = pixel(xi, yi);
    }

    return picture;
}




GrayImage * GrayImage::bilinearScale(uint16_t w, uint16_t h) const
{
	GrayImage * picture = new GrayImage(w, h);

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
			double mu = y-yi;

			picture -> pixel(_x, _y) = (1-lambda) * ((1-mu)*pixel(xi,yi) + mu*pixel(xi,y2))
															 +     lambda * ((1-mu)*pixel(x2,yi) + mu*pixel(x2,y2));
		}

		return picture;
	}
