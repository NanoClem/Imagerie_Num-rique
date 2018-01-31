///////////////////////////////////////////////////////////////////////////////
// IUT d'Aix-Marseille UniversitÃ©, site d'Arles
// DÃ©partement Informatique
// 2Ã¨me annÃ©e
// ----------------------------------------------------------------------------
// IN - SynthÃ¨se d'images - Rendu rÃ©aliste
// Auteur : SÃ©bastien Thon
// ----------------------------------------------------------------------------
// Base du TP 1
// Base d'un programme permettant d'afficher une scÃ¨ne composÃ©e d'un sol, de
// maisons et d'arbres. On placera des sources de lumiÃ¨re, on spÃ©cifiera les
// matÃ©riaux des diffÃ©rents objets et on utilisera un effet de brouillard.
// ----------------------------------------------------------------------------
// Compilation sous Windows :
//   g++ -Wall maison.cpp -o maison.exe -lfreeglut -lglu32 -lopengl32
// Compilation sous Linux :
//   g++ -Wall maison.cpp -o maison.exe -lfreeglut -lGLU -lGL
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>
#include "Texture.hpp"
#include "Breath.hpp"
#include "Smoke.hpp"

#define WIDTH   800										// Largeur de la fenÃªtre OpenGL
#define HEIGHT  600										// Hauteur de la fenÃªtre OpenGl

#define KEY_ESC 27										// Code ASCII de la touche Echap

float	xpos = 0, zpos = -50;												// Position de la camÃ©ra
int		angle_x = 45, angle_y = 45;									// Orientation de la camÃ©ra
int		mouse_x = 0, mouse_y = 0;										// Position de la souris

GLfloat position[] = { 10.0f, 20.0f, 5.0f, 1.0f };		// Position de la source de lumière


//Objets pour le plaquage des textures
Texture texture_sol(1, 128, 128, 3);
Texture texture_mur(2, 128, 128, 3);
Texture texture_facade(3, 256, 128, 3);
Texture texture_toit(4, 128, 128, 3);
Texture *texture_fumee = new Texture(5, 5, 10, 4);

//Fumée
list<Breath> breath;
Smoke smoke(1.0f, 0.0f, 10.0f, breath, 0.55f, 0.0f, texture_fumee);


//*****************************************************************
//* A FAIRE :
//* DÃ©clarer des tableaux contenant les caractÃ©ristiques (Ambient,
//* diffus, spÃ©culaire) pour diffÃ©rents matÃ©riaux :
//*    - sol
//*    - mur de maison
//*    - toit de maison
//*    - tronc d'arbre
//*    - feuillage d'arbre
//*
//* Par exemple, pour le matÃ©riau de sol:
//*   GLfloat MatAmbient_sol[] = {0.0f, 0.5f, 0.0f, 1.0f};	// On utilise des valeurs faibles pour Ambient (sombre, car Ã  l'ombre)
//*   GLfloat MatDiffuse_sol[] = {0.0f, 0.7f, 0.0f, 1.0f};	// On utilise des valeurs plus Ã©levÃ©es pour Diffuse (partie Ã©clairÃ©e)
//*   GLfloat MatSpecular_sol[]= {0.1f, 0.1f, 0.1f, 1.0f};	// Plus ces valeurs seront Ã©levÃ©es, et plus le matÃ©riau sera luisant
//*   GLfloat MatShininess_sol[1]={5.0f};					// Plus cette valeurs era Ã©levÃ©e (max=128) et plus le reflet sera petit
//*****************************************************************


///////////////////////////////////////////////////////////////////////////////
// Intitialisation de certains paramÃ¨tres d'OpenGL.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid initGL()
{
	glClearColor(0.4f, 0.4f, 0.4f, 1);		// Couleur servant Ã  effacer la fenÃªtre (noir)
  glShadeModel(GL_SMOOTH);							// ModÃ¨le d'ombrage : lissage de Gouraud
	glEnable(GL_CULL_FACE);								// Ne traite pas les faces cachÃ©es
	glEnable(GL_DEPTH_TEST);							// Active le Z-Buffer
	glDepthFunc(GL_LEQUAL);								// Mode de fonctionnement du Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Active la correction de perspective (pour ombrage, texture, ...)


	//*****************************************************************
	//* A FAIRE :
	//*
	//* 1. CrÃ©er la source de lumiÃ¨re 0 (GL_LIGHT0) en tant que source de
	//*    lumiÃ¨re directionnelle, en prÃ©cisant :
	//*      - sa position
	//*      - sa couleur ambiante
	//*      - sa couleur diffuse
	//*      - sa couleur spÃ©culaire
	//*
	//* 2. Activer la source de lumiÃ¨re 0.
	//*
	//* 3. Activer l'Ã©clairage gÃ©nÃ©ral
	//*****************************************************************

	// LUMIERE DIRECTIONNELLE
	// GLfloat direction[] = { 3.0, 5.0, 2.0, 0.0 };
	// glLightfv(GL_LIGHT0, GL_POSITION, direction);
  //
	// // Valeurs de couleurs
	// GLfloat Light0Amb[4]  = {0.5f, 0.5f, 0.5f, 1.0f};
	// GLfloat Light0Dif[4]  = {1.0f, 1.0f, 1.0f, 1.0f};
	// GLfloat Light0Spec[4] = {0.2f, 0.2f, 0.2f, 1.0f};
  //
	// // Fixe les paramètres de couleur de la lumière 0
	// glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Amb);
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Dif);
	// glLightfv(GL_LIGHT0, GL_SPECULAR, Light0Spec);
  //
	// glEnable(GL_LIGHT0);  // Active la lumière 0
	// glEnable(GL_LIGHTING); // Active l’éclairage
	// glDisable(GL_LIGHT0);



	// LUMIERE PONCTUELLE

	// GLfloat Light0Pos[4] = {5.0f, 20.0f, 10.0f, 1.0f};

	// Valeurs de couleurs
	GLfloat Light0Amb[4]  = {0.9f, 0.9f, 0.9f, 1.0f};
	GLfloat Light0Dif[4]  = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat Light0Spec[4] = {0.2f, 0.2f, 0.2f, 1.0f};

	// Fixe les paramètres de couleur de la lumière 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light0Spec);

	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING); // Active l’éclairage
	glEnable(GL_LIGHT0);  // Active la lumière 0


	//BROUILLARD
	// GLfloat fogColor[4] = {0.4f, 0.4f, 0.4f, 0.0f};	// Couleurs du brouillard
	// glFogf(GL_FOG_MODE, GL_EXP2); // ou GL_EXP
	// glFogf(GL_FOG_DENSITY, 0.03f); // défaut : 1.0f
	// glFogfv(GL_FOG_COLOR, fogColor);
	// glEnable(GL_FOG);

}


///////////////////////////////////////////////////////////////////////////////
// Affiche une sphère
///////////////////////////////////////////////////////////////////////////////
void affiche_sphere(double radius, int slices, int stacks, float pos[])
{
	GLfloat MatAmbient_sphere[4]   = {0.5f, 0.5f, 0.5f, 1.0f};	 // On utilise des valeurs faibles pour Ambient (sombre, car Ã  l'ombre)
	GLfloat MatDiffuse_sphere[4]   = {0.9f, 0.9f, 0.9f, 1.0f};	 // On utilise des valeurs plus Ã©levÃ©es pour Diffuse (partie Ã©clairÃ©e)
	GLfloat MatSpecular_sphere[4]  = {0.5f, 0.5f, 0.5f, 1.0f};		 // Plus ces valeurs seront Ã©levÃ©es, et plus le matÃ©riau sera luisant
	GLfloat MatShininess_sphere[1] = {5.0f};

	glPushMatrix();																					// Sauve la matrice de vue actuelle

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_sphere);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_sphere);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular_sphere);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_sphere);

	glTranslatef(pos[0], pos[1], pos[2]);	 								  // Positionne la sphere avec une translation
	glutSolidSphere(radius, slices, stacks);

	glPopMatrix();																					// Restaure la matrice de vue
}


///////////////////////////////////////////////////////////////////////////////
// Affiche le sol de la scÃ¨ne.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_sol()
{
	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du matÃ©riau
	//* crÃ©e pour le sol (utiliser glMaterialfv() pour les paramÃ¨tres
	//* ambiant, diffus, speculaire du matÃ©riau du sol).
	//*****************************************************************

	// Caractéristiques du sol
	GLfloat MatAmbient_sol[4]   = {0.0f, 0.60f, 0.30f, 1.0f};	 // On utilise des valeurs faibles pour Ambient (sombre, car Ã  l'ombre)
	GLfloat MatDiffuse_sol[4]   = {0.0f, 0.30f, 0.15f, 1.0f};	 // On utilise des valeurs plus Ã©levÃ©es pour Diffuse (partie Ã©clairÃ©e)
	GLfloat MatSpecular_sol[4]  = {0.1f, 0.1f, 0.1f, 1.0f};		 // Plus ces valeurs seront Ã©levÃ©es, et plus le matÃ©riau sera luisant
	GLfloat MatShininess_sol[1] = {5.0f};											 // Plus cette valeurs era Ã©levÃ©e (max=128) et plus le reflet sera petit

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_sol);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_sol);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular_sol);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_sol);

	//Texture
	texture_sol.use();

	glNormal3f( 0.0f, 1.0f, 0.0f);			// Normale
	glBegin(GL_QUADS);									// Affichage d'un quadrilatÃ¨re
			glTexCoord2f(0.0f, 0.0f);
		glVertex3d(-50, 0, -50);
			glTexCoord2f(0.0f, 10.0f);
		glVertex3d(-50, 0,  50);
			glTexCoord2f(10.0f, 10.0f);
		glVertex3d( 50, 0,  50);
			glTexCoord2f(10.0f, 0.0f);
		glVertex3d( 50, 0, -50);
	glEnd();
}



///////////////////////////////////////////////////////////////////////////////
// Affiche une maison.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    xp,yp,zp (in) : position de la maison.
//    yr       (in) : angle de rotation (en degrÃ©s) de la maison p/r Ã  l'axe y.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_maison( float xp, float yp, float zp, float yr )
{
	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(xp, yp, zp);							// Positionne la maison avec une translation
	glRotatef(yr, 0,1,0);								// et une rotation


	//*****************************************************************
	//* A FAIRE :
	//* Associer une normale Ã  chacun des polygones suivants. Pour cela
	//* faire appel Ã  glNormal3f() avant chacun des "glBegin(GL_QUADS)"
	//* et des "glBegin(GL_TRIANGLES)".
	//******************************************************************

	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du matÃ©riau
	//* crÃ©e pour les murs (utiliser glMaterialfv() pour les paramÃ¨tres
	//* ambiant, diffus, speculaire du matÃ©riau du mur).
	//*****************************************************************

	// Caractéristiques de la maison
	GLfloat MatAmbient_maison[4]   = {0.5f, 0.5f, 0.5f, 1.0f};	 // On utilise des valeurs faibles pour Ambient (sombre, car Ã  l'ombre)
	GLfloat MatDiffuse_maison[4]   = {1.0f, 1.0f, 1.0f, 1.0f};	 // On utilise des valeurs plus Ã©levÃ©es pour Diffuse (partie Ã©clairÃ©e)
	GLfloat MatSpecular_maison[4]  = {0.1f, 0.1f, 0.1f, 1.0f};	 // Plus ces valeurs seront Ã©levÃ©es, et plus le matÃ©riau sera luisant
	GLfloat MatShininess_maison[1] = {5.0f};										 // Plus cette valeurs era Ã©levÃ©e (max=128) et plus le reflet sera petit

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_maison);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_maison);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular_maison);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_maison);

	//Textures de la maison
	texture_facade.use();		// façade avant avec la porte
	// Mur de face
	glNormal3f( 0.0f, 0.0f, 1.0f);	// Normale
	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
		glVertex3d(-4, 5, 5);
			glTexCoord2f(0.0f, 1.0f);
		glVertex3d(-4, 0, 5);
			glTexCoord2f(1.0f, 1.0f);
		glVertex3d( 4, 0, 5);
			glTexCoord2f(1.0f, 0.0f);
		glVertex3d( 4, 5, 5);
	glEnd();


	texture_mur.use();			// murs de la maison
	// Mur arriÃ¨re
	glNormal3f( 0.0f, 0.0f, -1.0f);	// Normale
	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
		glVertex3d( 4, 5, -5);
			glTexCoord2f(0.0f, 1.0f);
		glVertex3d( 4, 0, -5);
			glTexCoord2f(1.0f, 1.0f);
		glVertex3d(-4, 0, -5);
			glTexCoord2f(1.0f, 0.0f);
		glVertex3d(-4, 5, -5);
	glEnd();

	texture_mur.use();			// murs de la maison
	// Mur gauche
	glNormal3f( -1.0f, 0.0f, 0.0f);	// Normale
	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
		glVertex3d(-4, 5, -5);
			glTexCoord2f(0.0f, 1.0f);
		glVertex3d(-4, 0, -5);
			glTexCoord2f(1.0f, 1.0f);
		glVertex3d(-4, 0,  5);
			glTexCoord2f(1.0f, 0.0f);
		glVertex3d(-4, 5,  5);
	glEnd();


	// Mur droit
	texture_mur.use();			// murs de la maison
	glNormal3f( 1.0f, 0.0f, 0.0f);	// Normale
	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
		glVertex3d(4, 5,  5);
			glTexCoord2f(0.0f, 1.0f);
		glVertex3d(4, 0,  5);
			glTexCoord2f(1.0f, 1.0f);
		glVertex3d(4, 0, -5);
			glTexCoord2f(1.0f, 0.0f);
		glVertex3d(4, 5, -5);
	glEnd();

	// Triangle avant
	texture_toit.use();
	glNormal3f( 0.0f, 0.0f, 1.0f);	// Normale
	glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f);
		glVertex3d( 0, 9, 5);
			glTexCoord2f(0.0f, 1.0f);
		glVertex3d(-4, 5, 5);
			glTexCoord2f(1.0f, 0.0f);
		glVertex3d( 4, 5, 5);
	glEnd();

	// Triangle arriÃ¨re
	texture_toit.use();
	glNormal3f( 0.0f, 0.0f, -1.0f);	// Normale
	glBegin(GL_TRIANGLES);
			glTexCoord2f(0.0f, 0.0f);
		glVertex3d( 0, 9, -5);
			glTexCoord2f(0.0f, 1.0f);
		glVertex3d( 4, 5, -5);
			glTexCoord2f(1.0f, 0.0f);
		glVertex3d(-4, 5, -5);
	glEnd();

//*****************************************************************
//* A FAIRE :
//* Remplacer le glColor3f() suivant par l'utilisation du matÃ©riau
//* crÃ©e pour le toit (utiliser glMaterialfv() pour les paramÃ¨tres
//* ambiant, diffus, speculaire du matÃ©riau du toit).
//*****************************************************************

	// Caractéristiques du sol
	GLfloat MatAmbient_toit[4]   = {0.15f, 0.08f, 0.0f, 1.0f};	 // On utilise des valeurs faibles pour Ambient (sombre, car Ã  l'ombre)
	GLfloat MatDiffuse_toit[4]   = {0.30f, 0.16f, 0.0f, 1.0f};	 // On utilise des valeurs plus Ã©levÃ©es pour Diffuse (partie Ã©clairÃ©e)
	GLfloat MatSpecular_toit[4]  = {0.1f, 0.1f, 0.1f, 1.0f};		 // Plus ces valeurs seront Ã©levÃ©es, et plus le matÃ©riau sera luisant
	GLfloat MatShininess_toit[1] = {5.0f};											 // Plus cette valeurs era Ã©levÃ©e (max=128) et plus le reflet sera petit

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_toit);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_toit);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular_toit);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_toit);

	// Toit versant droit
	texture_toit.use();
	glNormal3f( 0.707f, 0.707f, 0.0f );	// Normale
	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
		glVertex3d(0, 9,  5);
			glTexCoord2f(0.0f, 1.0f);
		glVertex3d(4, 5,  5);
			glTexCoord2f(1.0f, 1.0f);
		glVertex3d(4, 5, -5);
			glTexCoord2f(1.0f, 0.0f);
		glVertex3d(0, 9, -5);
	glEnd();

	// Toit versant gauche
	texture_toit.use();
	glNormal3f( -0.707f, 0.707f, 0.0f );	// Normale
	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
		glVertex3d( 0, 9, -5);
			glTexCoord2f(0.0f, 1.0f);
		glVertex3d(-4, 5, -5);
			glTexCoord2f(1.0f, 1.0f);
		glVertex3d(-4, 5,  5);
			glTexCoord2f(1.0f, 0.0f);
		glVertex3d( 0, 9,  5);
	glEnd();

	glPopMatrix();										// Restaure la matrice de vue
}



///////////////////////////////////////////////////////////////////////////////
// Affiche un arbre.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    xp,yp,zp (in) : position de l'arbre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_arbre( float xp, float yp, float zp )
{
	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(xp, yp, zp);							// Positionne l'arbre avec une translation

	//*****************************************************************
	//* A FAIRE :
	//* Afficher un arbre dont le tronc sera un cÃ´ne :
	//*     glutSolidCone()
	//* et le feuillage une sphÃ¨re :
	//*     glutSolidSphere()
	//* PrÃ©ciser le matÃ©riau pour chacun de ces Ã©lÃ©ments.
	//*****************************************************************



	glPopMatrix();										// Restaure la matrice de vue
}



///////////////////////////////////////////////////////////////////////////////
// Calcul du temps écoulé entre deux étapes d'animations d'un objet
///////////////////////////////////////////////////////////////////////////////
float mesure_temps_ecoule()
{
	static long temps_precedent = -1;
	long temps_actuel;
	float dt = 0;

	// Mesure du temps actuel :
	temps_actuel = glutGet(GLUT_ELAPSED_TIME);

	// - Si c'est la première fois que la fonction est appelée :
	if( temps_precedent == -1 )
	{
		temps_precedent = glutGet(GLUT_ELAPSED_TIME);
		dt = 0;
	}
	// - Sinon :
	else
	{
		dt = (float)(temps_actuel - temps_precedent) / 1000.0f;
		temps_precedent = temps_actuel;
	}

	return dt;
}




///////////////////////////////////////////////////////////////////////////////
// Affiche la fumée
///////////////////////////////////////////////////////////////////////////////
void affiche_fumee()
{
	texture_fumee->use();
	smoke.show();
}



///////////////////////////////////////////////////////////////////////////////
// Initialise les textures de la scène
///////////////////////////////////////////////////////////////////////////////
void initialise_scene()
{
	//Sol
	texture_sol.load((char *)"sol.png");
	texture_sol.define_filter(GL_NEAREST, GL_NEAREST);
	texture_sol.define_melting(GL_MODULATE);
	texture_sol.define_loop(GL_REPEAT, GL_REPEAT);

	//fumée
	texture_fumee->load((char *)"fumee.tga");
	texture_fumee->define_filter(GL_NEAREST, GL_NEAREST);
	texture_fumee->define_melting(GL_MODULATE);
	texture_fumee->define_loop(GL_REPEAT, GL_REPEAT);

	//Facade de la maison
	texture_facade.load((char *)"facade.png");
	texture_facade.define_filter(GL_NEAREST, GL_NEAREST);
	texture_facade.define_melting(GL_DECAL);
	texture_facade.define_loop(GL_REPEAT, GL_REPEAT);

	//Murs de la maison
	texture_mur.load((char *)"mur.png");
	texture_mur.define_filter(GL_NEAREST, GL_NEAREST);
	texture_mur.define_melting(GL_MODULATE);
	texture_mur.define_loop(GL_REPEAT, GL_REPEAT);

	//Toit de la maison
	texture_toit.load((char *)"toit.png");
	texture_toit.define_filter(GL_NEAREST, GL_NEAREST);
	texture_toit.define_melting(GL_MODULATE);
	texture_toit.define_loop(GL_REPEAT, GL_REPEAT);
}

///////////////////////////////////////////////////////////////////////////////
// Affiche les diffÃ©rents objets de la scÃ¨ne.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_scene()
{
	glEnable(GL_TEXTURE_2D);			// On active les textures pour ce qui doit en posséder
	affiche_sol();								// On affiche le sol.


	//*****************************************************************
	//* A FAIRE :
	//* Afficher quelques maisons et quelques arbres.
	//*
	//* Par exemple, on affiche ici une maison en (0,0,0),
	//* tournÃ©e de 20Â° :
	//*****************************************************************
	affiche_maison( 0, 0, 0, 20 );
	affiche_maison( 10, 0, 0, 360 );
	affiche_maison( 20, 0, 0, 350 );
	affiche_fumee();						  // On affiche la fumée
	glDisable(GL_TEXTURE_2D);


	glutSwapBuffers();							// Affiche la scÃ¨ne Ã  l'Ã©cran (affichage en double buffer)
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : affichage dans la fenÃªtre.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_display()
{
	// On efface les pixels de l'image (color buffer) et le Z-Buffer (depth buffer).
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// On initialise la matrice de vue avec la matrice identitÃ©.
	glLoadIdentity();

	// On applique une translation et une rotation Ã  la scÃ¨ne pour simuler
	// un dÃ©placement de camÃ©ra.
	glTranslatef(xpos,0,zpos);
	glRotatef(angle_x, 1,0,0);
	glRotatef(angle_y, 0,1,0);

	//*****************************************************************
	//* A FAIRE :
	//* Re-spÃ©cifier la position des sources de lumiÃ¨re avec glLightfv()
	//* pour qu'elles soient aussi affectÃ©es par la translation et la
	//* rotation qu'on vient d'appliquer Ã  la scÃ¨ne.
	//*****************************************************************
	// GLfloat Lightposition[3] = {5.0, 30.0, 0.0};
	// glLightfv(GL_LIGHT0, GL_POSITION, );
	affiche_sphere(2, 200, 200, position);

	//Calcul du temps écoulé entre deux étapes d'animation et fumée
	float dt = mesure_temps_ecoule();
	smoke.anime(dt);

	// On affiche la scÃ¨ne.
	affiche_scene();

	// On force OpenGL Ã  afficher avant de passer Ã  la suite.
	glFlush();
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : fonction appelÃ©e lorsqu'on redimensionne la fenÃªtre.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    width, height (in) : nouvelles largeur et hauteur de la fenÃªtre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des Ã©vÃ©nements clavier.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    key (in) : code ascii de la touche utilisÃ©e.
//    x,y (in) : coordonnÃ©es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'z':
			glutPostRedisplay();
			position[0] += 1;
			break;

		case 's':
			glutPostRedisplay();
			position[0] -= 1;
			break;

		case 'e':
			glutPostRedisplay();
			position[1] += 1;
			break;

		case 'a':
			glutPostRedisplay();
			position[1] -= 1;
			break;

		case 'd':
			glutPostRedisplay();
			position[2] += 1;
			break;

		case 'q':
			glutPostRedisplay();
			position[2] -= 1;
			break;

		case KEY_ESC:						// 'ECHAP' :
			exit(1);						// on quitte le programme
			break;
	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des touches speciales du clavier.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    key (in) : code ascii de la touche utilisÃ©e.
//    x,y (in) : coordonnÃ©es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	float speed = 1.0f;						// Vitesse de dÃ©placement de la camÃ©ra

	switch (key)
	{
		case GLUT_KEY_UP:					// FlÃ¨che vers le haut :
			zpos += speed;					// on dÃ©place la camÃ©ra selon z-
			glutPostRedisplay();			// et on demande le rÃ©affichage.
			break;

		case GLUT_KEY_DOWN:					// FlÃ¨che vers le bas :
			zpos -= speed;					// on dÃ©place la camÃ©ra selon z+
			glutPostRedisplay();			// et on demande le rÃ©affichage.
			break;

		case GLUT_KEY_LEFT:					// FlÃ¨che vers la gauche :
			xpos += speed;					// on dÃ©place la camÃ©ra selon x-
			glutPostRedisplay();			// et on demande le rÃ©affichage.
			break;

		case GLUT_KEY_RIGHT:				// FlÃ¨che vers la droite :
			xpos -= speed;					// on dÃ©place la camÃ©ra selon x+
			glutPostRedisplay();			// et on demande le rÃ©affichage.
			break;
	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion de clics souris.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    button (in) : code du bouton utilisÃ©.
//    state  (in) : Ã©tat du bouton.
//    x,y    (in) : coordonnÃ©es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des dÃ©placements de la souris.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    x,y    (in) : coordonnÃ©es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
	angle_x += y - mouse_y;						// Modifie la direction de vue de la camÃ©ra
	angle_y += x - mouse_x;						// en fonction de la position de la souris
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();						// Demande le rÃ©affichage
}


void timer(int v)
{
	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);
}


///////////////////////////////////////////////////////////////////////////////
// Fonction principale du programme.
//-----------------------------------------------------------------------------
// ParamÃ¨tres :
//    argc (in) : nombre d'arguments de la ligne de commande.
//    argv (in) : tableau de chaÃ®nes de caractÃ¨res contenant les arguments.
// Retour :
//    Un entier contenant le code de retour du programme.
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	// Initialisation de paramÃ¨tres de Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maison");

	// Intitialisation de paramÃ¨tres d'OpenGL
	initGL();

	// Charger les textures
	initialise_scene();

	// DÃ©claration des fonctions de call-back.
	glutDisplayFunc(&callback_display);
	glutTimerFunc(20, timer, 0);
	glutReshapeFunc(&callback_reshape);
	glutKeyboardFunc(&callback_keyboard);
	glutSpecialFunc(&callback_special);
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	// Boucle principale de Glut.
	glutMainLoop();

	// Code de retour
	return 1;
}
