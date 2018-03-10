//R. RAFFIN, IUT Aix-Marseille, dépt. Informatique - Arles
//TP événements, push & pop
//compilation par : g++ -Wall TP3.cpp -lGLEW -lGLU -lGL -lglut -o TP3
//compilation locale par :
// g++ -g -Wall -std=c++11 TP3.cpp Astre.cpp -I glew\include -I freeglut\include -L glew\lib -L freeglut\lib -lopengl32 -lglu32 -lfreeglut -lglew32 -o TP3
#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "Astre.hpp"

#define KEY_ESC 27

using namespace std;

float angle=0.0f;

float ax = 0.0f, ay = 0.0f;

//variables pour la gestion des paramètres de la fenêtre
float windowRatio = 1.0f;
int windowHeight = 500;
int windowWidth = 500;

float mouseAngleX = 0.0;
float mouseAngleY = 0.0;
int oldMouseX = windowHeight/2;
int oldMouseY = windowWidth/2;


void drawAxis() {
	glBegin(GL_LINES);
		//Ox, rouge
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(8.0, 0.0, 0.0);

		//Oy, vert
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 8.0, 0.0);

		//Oz, bleu
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 8.0);

	glEnd();
}

static void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Modification de la matrice de projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //remise à 0 (identité)
	gluPerspective(130.0, windowRatio, 0.1, 100); //définition d'une perspective (angle d'ouverture 130°,rapport L/H=1.0, near=0.1, far=100)

	//Modification de la matrice de modélisation de la scène
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Définition de la position de l'observateur
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //paramètres position(5.0, 5.0, 5.0), point visé(0.0, 0.0, 0.0), upVector - verticale (0.0, 1.0, 0.0)

	//rotation due aux mouvements de la souris
	glRotatef(mouseAngleX, 1.0, 0.0, 0.0);
	glRotatef(mouseAngleY, 0.0, 1.0, 0.0);

	//dessin des axes du repère
	drawAxis();

	//Dessin de la théière centrée en (0, 0, 0)
	//Tournant autour de Oy. Ajout de la sphère rouge tournant autour de la théière
	// glPushMatrix();
	// 	glColor3f(0.2, 0.5, 0.3);
	// 	glRotatef(angle, 0.0, 1.0, 0.0);
	// 	glutSolidTeapot(2.0);
	//
	// 	glColor3f(1.0, 0.0, 0.0);
	// 	glRotatef(1.2*angle, 0.0, 1.0, 0.0);	//vitesse*angle
	// 	glTranslatef(3.0, 0.0, 0.0);
	// 	glutWireSphere(0.5, 10, 10);
	// glPopMatrix();

	//Dessin du tore tournant autour de Ox.
	//Ajout de la sphère bleue tournant autour du tore
	//tore
	// glColor3f(0.4, 0.4, 0.4);
	// glRotatef(0.8*angle, 1.0, 0.0, 0.0);
	// glTranslatef(0.0,0.0, 7.0);
	// glutSolidTorus(1.0, 2.0, 10, 5);
	//
	// 	//sphère bleue
	// 	glColor3f(0.0, 0.0, 1.0);
	// 	glRotatef(1.5*angle, 0.0, 1.0, 0.0);
	// 	glTranslatef(3.0, 0.0, 0.0);
	// 	glutWireSphere(0.5, 10, 10);



	//SOLEIL
  GLfloat *sun_color = new float[3];
	sun_color[0] = 1.0;
	sun_color[1] = 1.0;
	sun_color[2] = 0.0;
	Astre *soleil = new Astre(2.0, 0.5, 0.0, angle, sun_color);
	soleil->withoutSatellite();

	//MARS
	GLfloat *mars_color = new float[3];
	mars_color[0] = 1.0;
	mars_color[1] = 0.0;
	mars_color[2] = 0.0;
	Astre *mars = new Astre(0.5, 2.0, 5.0, angle, mars_color);
	mars->withoutSatellite();

	//TERRE AVEC LA LUNE EN ORBITE
	GLfloat *earth_color = new float[3];
	earth_color[0] = 0.0;
	earth_color[1] = 0.0;
	earth_color[2] = 1.0;
	Astre *terre = new Astre(0.7, 3.0, 7.0, angle, earth_color);
	terre->withSatellite();

	glutSwapBuffers();
}

//A lier à la glutIdleFunc
static GLvoid callback_Idle()
{
	angle += 0.03f;
	glutPostRedisplay();

}

// fonction de call-back pour la gestion des evenements clavier
static GLvoid callback_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	  case KEY_ESC:
		cout << "callback_Keyboard - " << "sortie de la boucle de rendu" << endl;
			glutLeaveMainLoop ( ); //retour au main()
		break;

	  default:
	    	cerr << "callback_Keyboard - touche " << key << " non active." << endl;
	    break;
	  }
}


// fonction de call-back pour le redimensionnement de la fenêtre
static GLvoid callback_Window(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	windowWidth = width;
	windowHeight = height;

	windowRatio = float(windowWidth) / float(windowHeight);

	cout << "callback_Window - " << "new width " << windowWidth << " new height " << windowHeight << endl;
}

GLvoid gestionFleche(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP :
			ay += int(1);
			cout << "up \n";
		break;

		case GLUT_KEY_DOWN :
			ay -= int(1);
			cout << "down \n";
		break;
	}
	glutPostRedisplay();
}

static GLvoid callback_Mouse(int wx, int wy) {
//rotation de la scene suivant les mouvements de la souris
	int dx = oldMouseX - wx;
	int dy = oldMouseY - wy;

	oldMouseX = wx;
	oldMouseY = wy;

	mouseAngleX += dy;
	mouseAngleY += dx;

	cout << "callback_Mouse - " << "mouseAngleX " << mouseAngleX << " mouseAngleY " << mouseAngleY << endl;
}


static void InitializeGlutCallbacks()
{
	//quelle fonction est appelée au rendu ?
	glutDisplayFunc(RenderScene);

	//quelle fonction est appelée quand le GPU est en attente ?
	glutIdleFunc(callback_Idle);

	//quelle fonction est appelée pour traiter les événements du clavier (classique) ?
	glutKeyboardFunc(callback_Keyboard);

	//quelle fonction est appelée pour traiter les événements souris ?
	glutMotionFunc(callback_Mouse);

	//quelle fonction est appelée pour traiter les événements sur la fenêtre ?
	glutReshapeFunc(callback_Window);

	//quelle fonction est appelée pour traiter les touches spéciales du clavier ?
	glutSpecialFunc(&gestionFleche);

}

static void InitializeGL() {
	GLfloat lightPosition [] = { 0.0f, 10.0f, 0.0f, 0.0 };

	//Crée une source de lumière directionnelle
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Définit un modèle d'ombrage
	glShadeModel(GL_SMOOTH);

	//Z Buffer pour la suppression des parties cachées
	glEnable(GL_DEPTH_TEST);

	//La variable d'état de couleur GL_AMBIENT_AND_DIFFUSE
	//est définie par des appels à glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("TP3 : événements, hiérarchies");


	//toujours après l'initialisation de glut
	GLenum res = glewInit();

	if (res != GLEW_OK) {
		cerr << "Error: " << glewGetErrorString(res) << endl;
		return (EXIT_FAILURE);
	}


	InitializeGlutCallbacks();
	InitializeGL();

	glutMainLoop();

	return (EXIT_SUCCESS);
}
