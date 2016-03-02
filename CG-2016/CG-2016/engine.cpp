#include "windows.h" 
#include <GL/glut.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <tinyxml.h>
#include <tinystr.h>

using namespace std;

#define _USE_MATH_DEFINES
#include <math.h>

float angle = 0;
float axis = 1;
int Z = 0;
int X = 0;

vector<double> xs;
vector<double> ys;
vector<double> zs;

int tam = 0;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void drawFromFile() {

	double r, g, b;

	for (int i = 0; i <= tam; i=i+3)
	{
		r = ((double)rand() / (RAND_MAX));
		g = ((double)rand() / (RAND_MAX));
		b = ((double)rand() / (RAND_MAX));

		glBegin(GL_TRIANGLES);
			glColor3d(r, g, b);
			glVertex3d(xs[i], ys[i], zs[i]);
			glVertex3d(xs[i+1], ys[i+1], zs[i+1]);
			glVertex3d(xs[i+2], ys[i+2], zs[i+2]);
		glEnd();
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(0.0, 5.0, 1.0,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	// put the geometric transformations here
	glTranslatef(X, 0, Z);

	if (axis == 1) {
		glRotatef(angle, 0, 1, 0);
	}
	else {
		glRotatef(angle, 0, 0, 1);
	}
	
	// put drawing instructions here
	drawFromFile();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events

void responseKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'q': axis=1; break;
	case 'w': axis=0; break;
	default:
		break;
	}
	glutPostRedisplay();
}

void responseKeyboardSpecial(int key_code, int x1, int y1) {

	switch (key_code)
	{
	case GLUT_KEY_UP: Z++; break;
	case GLUT_KEY_DOWN: Z--; break;
	case GLUT_KEY_LEFT: X--; break;
	case GLUT_KEY_RIGHT: X++; break;
	case GLUT_KEY_F1: angle++; break;
	case GLUT_KEY_F2: angle--; break;
	default:
		break;
	}
	glutPostRedisplay();
}

// write function to process menu events




unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

int readFile3d(string filemodelo, char delem) {
	vector<string> aux;
	string line;
	int l = 0;
	int nVertices;
	ifstream myfile(filemodelo);


	getline(myfile, line);
	nVertices = stold(line);

	//limpar o aray pois tens os vertices do ultimo ficheiro
	//tam = 0;
	//xs.clear();
	//ys.clear();
	//zs.clear();

	//é necessario testar se o ficehiro nao foi aberto usar exceptions pois o open nao retorna bool

	while (getline(myfile, line))
	{
		aux.clear();
		int lid = split(line, aux, delem);
		tam++;
		string x = aux[0];
		string y = aux[1];
		string z = aux[2];
		
		xs.push_back(stold(x));
		ys.push_back(stold(y));
		zs.push_back(stold(z));
	}
	myfile.close();
	return nVertices;
}

int main(int argc, char **argv) {

	char* pFilename = "teste.xml"; 
	TiXmlDocument doc;

	if (doc.LoadFile(pFilename))
	{
		try
		{
			for (TiXmlElement* elem = doc.FirstChildElement("scene"); elem != NULL; elem = elem->NextSiblingElement()) {

				const char* file = elem->FirstChildElement("model")->Attribute("file");

				readFile3d(file, ';');
			}
		}
		catch (const std::exception&)
		{
			printf("Failed to load file \"%s\"\n", pFilename);
		}
		
	}
	else
	{
		printf("Failed to open file \"%s\"\n", pFilename);
	}

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");


	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// put here the registration of the keyboard and menu callbacks

	glutKeyboardFunc(responseKeyboard);
	glutSpecialFunc(responseKeyboardSpecial);

	// put here the definition of the menu 

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}