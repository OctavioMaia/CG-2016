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

vector<double> rs;
vector<double> gs;
vector<double> bs;

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

	for (int i = 0,j=0; i <= tam; i=i+3,j++)
	{
		

		glBegin(GL_TRIANGLES);
			glColor3d(rs[j], gs[j], bs[j]);
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
	gluLookAt(-5.0, 5.0, 20.0,
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
	case 'x': axis = 0; glutPostRedisplay(); break;
	case 'y': axis = 1; glutPostRedisplay(); break;
	case 'z': axis = 2; glutPostRedisplay(); break;
	default:
		break;
	}
}

void responseKeyboardSpecial(int key_code, int x1, int y1) {

	switch (key_code)
	{
	case GLUT_KEY_UP: Z++; glutPostRedisplay(); break;
	case GLUT_KEY_DOWN: Z--; glutPostRedisplay(); break;
	case GLUT_KEY_LEFT: X--; glutPostRedisplay(); break;
	case GLUT_KEY_RIGHT: X++; glutPostRedisplay(); break;
	case GLUT_KEY_F1: angle++; glutPostRedisplay(); break;
	case GLUT_KEY_F2: angle--; glutPostRedisplay(); break;
	default:
		break;
	}
	
}

// write function to process menu events

void menuCreate(int id_op) {
	switch (id_op)
	{
		//
	case 1: glPolygonMode(GL_FRONT, GL_LINE); glutPostRedisplay(); break;
		//
	case 2: glPolygonMode(GL_FRONT, GL_FILL); glutPostRedisplay(); break;
		//
	case 3: glPolygonMode(GL_FRONT, GL_POINT); glutPostRedisplay(); break;
		//
	case 4: glPolygonMode(GL_FRONT, GL_LINE); glutPostRedisplay(); break;
	default:
		break;
	}

}



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

	//� necessario testar se o ficehiro nao foi aberto usar exceptions pois o open nao retorna bool

	cout << nVertices;

	for (int i = 0; i <= nVertices; i++)
	{
		getline(myfile, line);
		aux.clear();
		int lid = split(line, aux, delem);

		string x = aux[0];
		string y = aux[1];
		string z = aux[2];

		if (i % 3 == 0){
			rs.push_back((double)rand() / (RAND_MAX));
			gs.push_back((double)rand() / (RAND_MAX));
			bs.push_back((double)rand() / (RAND_MAX));
		}

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
	const char* file;
	if (doc.LoadFile(pFilename))
	{
		try
		{
			for (TiXmlElement* elem = doc.FirstChildElement("scene")->FirstChildElement("model"); elem != NULL; elem = elem->NextSiblingElement()) {

				cout << "ola";

				file = elem->Attribute("file");

				cout << file << "\n";

				cout << "estou no ciclo";

				tam+=readFile3d(file, ';');
				cout << tam << "\n";
				cout << "ola2";
			}
		}
		catch (const std::exception&)
		{
			cout << file << "\n";
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

	glPolygonMode(GL_FRONT, GL_LINE);

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// put here the registration of the keyboard and menu callbacks

	glutKeyboardFunc(responseKeyboard);
	glutSpecialFunc(responseKeyboardSpecial);

	// put here the definition of the menu 

	glutCreateMenu(menuCreate);
	glutAddMenuEntry("Wire", 1);
	glutAddMenuEntry("Fill", 2);
	glutAddMenuEntry("Point", 3);
	glutAddMenuEntry("Change Colors", 4);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}