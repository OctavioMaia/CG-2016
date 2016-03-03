#define _USE_MATH_DEFINES
#include <math.h>
#include "windows.h" 
#include <GL/glut.h>
#include <chrono>

#include "Figura.h"
#include <tinyxml.h>
#include <tinystr.h>

using namespace std;

float angle = 0;
int axis = 1;
int Z = 0;
int X = 0;

vector<Figura> figuras;
bool multiColor=false;

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

	

	// for para percorrer as figuras todas
	for (int i = 0; i < figuras.size(); i++)
	{
		cout << "drawFromFile " << figuras.size() << "\n";
		Figura fg = figuras[i];
		fg.drawFigure(multiColor);
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 20.0,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	// put the geometric transformations here
	glTranslatef(X, 0, Z);

	switch (axis)
	{
		case 0: glRotatef(angle, 1, 0, 0);
		case 1: glRotatef(angle, 0, 1, 0);
		case 2: glRotatef(angle, 0, 0, 1);
	default: 
		break;
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
			// Modo Line
		case 1: glPolygonMode(GL_FRONT, GL_LINE); glutPostRedisplay(); break;
			// Modo FILL
		case 2: glPolygonMode(GL_FRONT, GL_FILL); glutPostRedisplay(); break;
			// Modo Point
		case 3: glPolygonMode(GL_FRONT, GL_POINT); glutPostRedisplay(); break;
			// Random Colors in all triangles
		case 4: multiColor=true; glutPostRedisplay(); break;
			// Single color blue 0.0 0.0 1.0
		case 5: glColor3d(0.0, 0.0, 1.0); multiColor = false; glutPostRedisplay(); break;
			// Single color red 1.0 0.0 0.0
		case 6: glColor3d(1.0, 0.0, 0.0); multiColor = false; glutPostRedisplay(); break;
			//Single Color green 0.0 1.0 0.0
		case 7: glColor3d(0.0, 1.0, 0.0); multiColor = false; glutPostRedisplay(); break;

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
	vector<string> campos;
	string line;
	int nVertices;

	ifstream myfile(filemodelo);

	getline(myfile, line);
	nVertices =  stoi(line);

	Figura fg = Figura::Figura(filemodelo, nVertices);

	for (int i = 0; i < nVertices; i++)
	{
		getline(myfile, line);
		campos.clear();
		split(line, campos, delem);

		fg.addPonto(stold(campos[0]), stold(campos[1]), stold(campos[2]));
	}

	fg.gerarCores();

	figuras.push_back(fg);

	myfile.close();

	return nVertices;
}

int main(int argc, char **argv) {

	char* pFilename = argv[1];
	TiXmlDocument doc;
	const char* file;
	if (doc.LoadFile(pFilename))
	{
		try
		{
			for (TiXmlElement* elem = doc.FirstChildElement("scene")->FirstChildElement("model"); elem != NULL; elem = elem->NextSiblingElement()) {

				file = elem->Attribute("file");

				cout << "Go read file: " << file << "\n";

				readFile3d(file, ';');
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
	glutAddMenuEntry("Multiple Colores", 4);
	glutAddMenuEntry("Single Color: Blue", 5);
	glutAddMenuEntry("Single Color: Red", 6);
	glutAddMenuEntry("Single Color: Green", 7);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}