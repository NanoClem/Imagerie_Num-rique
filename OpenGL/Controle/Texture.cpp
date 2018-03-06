#define STB_IMAGE_IMPLEMENTATION
#include <GL/glut.h>
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Texture.hpp"


//Constructeur
Texture::Texture(GLuint _id, int _width, int _height, int _comp)
  : id(_id), width(_width), height(_height), comp(_comp)
  {}


//Destructeur
Texture::~Texture()
{}


//Charger une image pour en faire une texture
bool Texture::load(char *filename)
{
  glGenTextures(1, &id);
  unsigned char *img = stbi_load(filename, &width, &height, &comp, 0);
  GLenum rgb_mode = (comp == 3 ? rgb_mode = GL_RGB : GL_RGBA);

  if(img != NULL)
  {
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, comp, width, height, 0, rgb_mode, GL_UNSIGNED_BYTE, img);
    if(mimap)
    {
      gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
                        width, height,
                        GL_RGB, GL_UNSIGNED_BYTE, img);
    }
    delete [] img;
  }
}


//Définir la texture courrante
void Texture::use()
{
  glBindTexture(GL_TEXTURE_2D, id);
}


//Définir le mode de filtrage
void Texture::define_filter(GLint min_mode, GLint mag_mode)
{
  use();  //texture courrante
  if(mimap)
  {
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
  }
  else
  {
    glTexParameteri( GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    min_mode );

    glTexParameteri( GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    mag_mode );
  }
}


//Définir le mode de bouclage
void Texture::define_loop(GLint mode_axe_s, GLint mode_axe_t)
{
  use();
  glTexParameteri( GL_TEXTURE_2D,
                   GL_TEXTURE_WRAP_S,
                   mode_axe_s );

 glTexParameteri( GL_TEXTURE_2D,
                  GL_TEXTURE_WRAP_T,
                  mode_axe_t );
}


//Définir le mode de mélange des textures
void Texture::define_melting(GLint mode)
{
  glTexEnvf( GL_TEXTURE_ENV,
             GL_TEXTURE_ENV_MODE,
             mode);
}
