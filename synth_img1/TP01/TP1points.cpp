//2016 R. RAFFIN, IUT Aix-Marseille, dept. Informatique - Arles
//TP simple, affichages de quelques points
//compilation par :
//g++ -g -Wall -std=c++11 TP1points.cpp Point.cpp Cercle.cpp -I glew\include -I freeglut\include -L glew\lib -L freeglut\lib -lopengl32 -lglu32 -lfreeglut -lglew32 -o TP1points

#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Cercle.hpp"

using namespace std;

GLuint leVBO;

static void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);


//Liaison avec le buffer de vertex
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, leVBO);
	glVertexPointer(3, GL_FLOAT, 0, 0); //description des données pointées

	glDrawArrays(GL_POINTS, 0, 9); //9 éléments à utiliser pour le dessin

	glDisableClientState(GL_VERTEX_ARRAY); //plus besoin de vertexArray

	glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderScene);
}


//Calcule des coordonées aléatoires comprises dans l'intervalle [-1; 1]
void randCoords(float vertices[], int nbVertex)
{
	srand( time(NULL) );                  //initialisation de rand()
	for(size_t i = 0; i < nbVertex; i++)
		vertices[i] = ( rand()/(double)RAND_MAX ) * (1+1)-1;
}


//Crée un objet de type Cercle et renvoie les coordonées en 3D des points
float *createCircle(float CentreX, float CentreY, float rayon)
{
	Cercle *cercle = new Cercle(CentreX, CentreY, rayon);
	return cercle->getCoords();
}


static void CreateVertexBuffer()
{
	float vertices[24]; 	 		// 9 points à 3 coordonnées x,y,z par point

	float randVertices[27];			// 9 points à coordonnées aléatoires
	randCoords(randVertices, 27);	// remplissage du tableau de coords

	float *circleVertices = createCircle(0, 0, 1);   //Cercle de centre (0,0) et de rayon 1


//1er sommet
	// vertices[0] = 0.0f;
	// vertices[1] = 0.0f;
	// vertices[2] = 0.0f;

//2ème sommet
	vertices[0] = 0.25f;
	vertices[1] = 0.25f;
	vertices[2] = 0.0f;

//3ème sommet
	vertices[3] = 0.0f;
	vertices[4] = 0.9f;
	vertices[5] = 0.0f;

//4ème sommet
	vertices[6] = -0.25f; 	//pour tester
	vertices[7] = 0.25f;
	vertices[8] = 0.0f;

//5ème sommet
	vertices[9] = -.9f;
	vertices[10] = 0.0f;
	vertices[11] = 0.0f;

//6ème sommet
	vertices[12] = -0.25f;
	vertices[13] = -0.25f;
	vertices[14] = 0.0f;

//7ème sommet
	vertices[15] = 0.0f;
	vertices[16] = -0.9f;
	vertices[17] = 0.0f;

//8ème sommet
	vertices[18] = 0.25f;
	vertices[19] = -0.25f;
	vertices[20] = 0.0f;

//9ème sommet
	vertices[21] = 0.9f;
	vertices[22] = 0.0f;
	vertices[23] = 0.0f;

 	glGenBuffers(1, &leVBO); //génération d'une référence de buffer object
	glBindBuffer(GL_ARRAY_BUFFER, leVBO); //liaison du buffer avec un type tableau de données
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*24, vertices, GL_STATIC_DRAW); //création et initialisation du container de données (9 sommets -> 27 float)
	// glBufferData(GL_ARRAY_BUFFER, sizeof(float)*27, randVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*27, circleVertices, GL_STATIC_DRAW);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("TP1 : quelques points");

	InitializeGlutCallbacks();

	//toujours après l'initialisation de glut
	GLenum res = glewInit();

	if (res != GLEW_OK) {
		cerr << "Error: " << glewGetErrorString(res) << endl;
		return (EXIT_FAILURE);
	}

	//cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	CreateVertexBuffer();

	glutMainLoop();

	return (EXIT_SUCCESS);
}
