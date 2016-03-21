#define _USE_MATH_DEFINES

#include <math.h>
#include "windows.h" 

#include <GL\glew.h>
#include <GL\glut.h>


#pragma comment(lib, "glew32.lib")


#include <chrono>
#include "Referencial.h"

#include "tinyxml.h"
#include "tinystr.h"

using namespace std;
#define AngC  M_PI / 180
float angle;
float betaCam;
float alfaCam;
float rCam;
float betaLook;
float alfaLook;

Referencial princRef;

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

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

	//-rCam*cos(AngC*betaLook)*sin(AngC*alfaLook), -rCam*sin(AngC*betaLook), -rCam*cos(AngC*betaLook)*cos(AngC*alfaLook),
	gluLookAt(rCam*cos(AngC*betaCam)*sin(AngC*alfaCam), rCam*sin(AngC*betaCam), rCam*cos(AngC*betaCam)*cos(AngC*alfaCam),
		0, 0, 0,
		0.0f, 1.0f, 0.0f);

	// put the geometric transformations here
	glRotatef(angle,0.0,1.0,0.0);
	
	// put drawing instructions here
	princRef.apply();

	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events

void responseKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
		case 'w': if (betaCam < 90) { betaCam--; } glutPostRedisplay(); break;
		case 's': if (betaCam > -90) { betaCam++; } glutPostRedisplay(); break;
		case 'a': alfaCam--; glutPostRedisplay(); break;
		case 'd': alfaCam++; glutPostRedisplay(); break;
		case 'r': rCam=rCam+0.25; glutPostRedisplay(); break;
		case 't': rCam=rCam-0.25; glutPostRedisplay(); break;
		default:
			break;
	}
}


void responseKeyboardSpecial(int key_code, int x1, int y1) {

	switch (key_code)
	{
		//case GLUT_KEY_UP: if (betaLook < 90) { betaLook++; } glutPostRedisplay(); break;
		//case GLUT_KEY_DOWN: if (betaLook > -90) { betaLook--; } glutPostRedisplay(); break;
		//case GLUT_KEY_LEFT: alfaLook++; glutPostRedisplay(); break;
		//case GLUT_KEY_RIGHT: alfaLook--; glutPostRedisplay(); break;
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

void readModels(TiXmlElement* elem, Referencial* ref){
	const char* filemodelo;
	TiXmlElement* elemFunc = elem->FirstChildElement("models");

	for (elemFunc = elemFunc->FirstChildElement("model"); elemFunc != NULL; elemFunc = elemFunc->NextSiblingElement()) {

		filemodelo = elemFunc->Attribute("file");

		cout << "Go read file: " << filemodelo << "\n";

		vector<string> campos;
		string line;
		int nVertices;

		ifstream myfile(filemodelo);

		getline(myfile, line);
		nVertices = stoi(line);

		Figura fg = Figura::Figura(filemodelo, nVertices);

		for (int i = 0; i < nVertices; i++)
		{
			getline(myfile, line);
			campos.clear();
			split(line, campos, ';');

			fg.addPonto(stold(campos[0]), stold(campos[1]), stold(campos[2]));
		}

		fg.gerarCores();

		ref->addFigura(fg);

		myfile.close();

	}
}

void readTranslate(TiXmlElement* elem, Referencial* ref) {
	TiXmlElement* elem1;

	Translacao trans = Translacao::Translacao();

	if ((elem1 = elem->FirstChildElement("translate")) != NULL) {
		
		const char* valeu;

		cout << "translate\n";
		if (valeu = elem1->Attribute("X")) {
			trans.setX(atof(valeu));
			cout << "X=" << valeu << "\n";
		}

		if (valeu = elem1->Attribute("Y")) {
			trans.setY(atof(valeu));
			cout << "Y=" << valeu << "\n";
		}
		if (valeu = elem1->Attribute("Z")) {
			trans.setZ(atof(valeu));
			cout << "Z=" << valeu << "\n";
		}
		ref->setTranslacao(trans);
	}
}


void readScale(TiXmlElement* elem, Referencial* ref) {
	TiXmlElement* elem1;

	Escala scale = Escala::Escala();

	//<scale X = "0.5" Y = "0.5" Z = "0.5" / >

	if ((elem1 = elem->FirstChildElement("scale")) != NULL) {

		const char* valeu;

		cout << "translate\n";
		if (valeu = elem1->Attribute("X")) {
			scale.setX(atof(valeu));
			cout << "X=" << valeu << "\n";
		}

		if (valeu = elem1->Attribute("Y")) {
			scale.setY(atof(valeu));
			cout << "Y=" << valeu << "\n";
		}
		if (valeu = elem1->Attribute("Z")) {
			scale.setZ(atof(valeu));
			cout << "Z=" << valeu << "\n";
		}
		ref->setEscala(scale);
	}
}

void readRotate(TiXmlElement* elem, Referencial* ref) {
	TiXmlElement* elem1;

	//<rotate angle="45" axisX="0" axisY="1" axisZ="0" />
	Rotacao rot = Rotacao::Rotacao();

	if ((elem1 = elem->FirstChildElement("rotate")) != NULL) {
		const char* valeu;;

		if (valeu = elem1->Attribute("angle")) {
			rot.setAngle(atof(valeu));
			cout << "angle=" << atof(valeu) << "\n";
		}

		if (valeu = elem1->Attribute("axisX")) {
			rot.setX(atof(valeu));
			cout << "axisX=" << atof(valeu) << "\n";
		}
		if (valeu = elem1->Attribute("axisY")) {
			rot.setY(atof(valeu));
			cout << "axisY=" << atof(valeu) << "\n";
		}
		if (valeu = elem1->Attribute("axisZ")) {
			rot.setZ(atof(valeu));
			cout << "axisZ=" << atof(valeu) << "\n";
		}
		ref->setRotacao(rot);


		cout << "ola";
	}

}

void loadElementChild(TiXmlElement* elem, Referencial* refPai) {

	TiXmlElement* elemFunc = elem;

	readTranslate(elemFunc, refPai);
	readRotate(elemFunc, refPai); 
	readScale(elemFunc, refPai);
	readModels(elemFunc, refPai);

	for (elemFunc = elemFunc->FirstChildElement("group"); elemFunc != NULL; elemFunc = elemFunc->NextSiblingElement()) {
		Referencial refFilho = Referencial::Referencial();

		

		loadElementChild(elemFunc,&refFilho);

		refPai->addFilho(refFilho);
	}
}

void readFileXML(char* file) {

	princRef = Referencial::Referencial();

	TiXmlDocument doc;

	if (doc.LoadFile(file))
	{
		try
		{
			for (TiXmlElement* elem = doc.FirstChildElement("scene")->FirstChildElement("group"); elem != NULL; elem = elem->NextSiblingElement()) {
				Referencial local = Referencial::Referencial();
				
				loadElementChild(elem,&local);

				princRef.addFilho(local);
			}
		}
		catch (const std::exception&)
		{
			cout << file << "\n";
			printf("Failed to load file \"%s\"\n", file);
		}
	}
	else
	{
		printf("Failed to open file \"%s\"\n", file);
	}
}

int main(int argc, char **argv) {
	angle = 0;
	betaCam = 0;
	alfaCam = 0;
	rCam = 8;
	betaLook = 0;
	alfaLook = 0;

	

	readFileXML(argv[1]);
	
	
	glEnableClientState(GL_VERTEX_ARRAY);


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
	glutAddMenuEntry("Multiple Colors", 4);
	glutAddMenuEntry("Single Color: Blue", 5);
	glutAddMenuEntry("Single Color: Red", 6);
	glutAddMenuEntry("Single Color: Green", 7);
	glutAttachMenu(GLUT_LEFT_BUTTON);


	glewInit();


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	




	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}