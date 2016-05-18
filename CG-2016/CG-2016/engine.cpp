#define _USE_MATH_DEFINES


#include "Reader.h"
#include "Scene.h"

#include <math.h>
#include "windows.h" 

#include <GL\glew.h>
#pragma comment(lib, "glew32.lib")



#include <chrono>

using namespace std;
#define AngC  M_PI / 180
float angle;
float betaCam;
float alfaCam;
float rCam;
float betaLook;
float alfaLook;

int frame = 0;
int timebase = 0;
float fps = 60.0f;

float camX = 0, camY, camZ = 5;
int startX, startY, tracking = 0;

int alpha = 0, beta = 0, r = 5;

Scene sceneMain;


bool multiColor=false;

void updateFPS() {

	frame += 1;

	int time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {

		fps = frame * 1000.0 / (time - timebase);
		timebase = time;
		frame = 0;
	}

	char sFPS[32];
	sprintf(sFPS, "CG@DI-UM %.4f", fps);

	glutSetWindowTitle(sFPS);
}

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

	
	gluLookAt(rCam*cos(AngC*betaCam)*sin(AngC*alfaCam), rCam*sin(AngC*betaCam), rCam*cos(AngC*betaCam)*cos(AngC*alfaCam),
		0,0,0,
		0.0f, 1.0f, 0.0f);

	// put the geometric transformations here
	//glRotatef(angle,0.0,1.0,0.0);
	
	// put drawing instructions here
	sceneMain.apply(1.0/fps);

	updateFPS();

	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events

void responseKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
		case 'w': if (betaCam < 90) { betaCam+=10; } glutPostRedisplay(); break;
		case 's': if (betaCam > -90) { betaCam-=10; } glutPostRedisplay(); break;
		case 'a': alfaCam-=10; glutPostRedisplay(); break;
		case 'd': alfaCam+=10; glutPostRedisplay(); break;
		case 'r': rCam=rCam+1; glutPostRedisplay(); break;
		case 't': rCam=rCam-1; glutPostRedisplay(); break;
		default:
			break;
	}
}

void responseKeyboardSpecial(int key_code, int x1, int y1) {

	switch (key_code)
	{
		case GLUT_KEY_UP: if (betaLook < 90) { betaLook++; } glutPostRedisplay(); break;
		case GLUT_KEY_DOWN: if (betaLook > -90) { betaLook--; } glutPostRedisplay(); break;
		case GLUT_KEY_LEFT: alfaLook++; glutPostRedisplay(); break;
		case GLUT_KEY_RIGHT: alfaLook--; glutPostRedisplay(); break;
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
		default:
			break;
	}

}


void processMouseButtons(int button, int state, int xx, int yy)
{
	if (state == GLUT_DOWN) {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {

			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy)
{
	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {

		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux *							     sin(betaAux * 3.14 / 180.0);
}


int main(int argc, char **argv) {
	angle = 0;
	betaCam = 10;
	alfaCam = 0;
	rCam = 20;
	betaLook = 0;
	alfaLook = 0;

	sceneMain = readFileXML(argv[1]);

	//DevIL Init
	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1500, 800);
	glutCreateWindow("CG@DI-UM");

	glewInit();

	glPolygonMode(GL_FRONT, GL_FILL);

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);


	// put here the registration of the keyboard and menu callbacks
	glutKeyboardFunc(responseKeyboard);
	glutSpecialFunc(responseKeyboardSpecial);

	// mouse callbacks
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

	// put here the definition of the menu 
	glutCreateMenu(menuCreate);
	glutAddMenuEntry("Wire", 1);
	glutAddMenuEntry("Fill", 2);
	glutAddMenuEntry("Point", 3);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}