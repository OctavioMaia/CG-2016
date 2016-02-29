#include "windows.h" 
#include <GL/glut.h>
#include <chrono>


#define _USE_MATH_DEFINES
#include <math.h>

float angle = 0;
float axis = 1;
int Z = 0;
int X = 0;
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



void drawObjectFromPoints() {

}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	// put the geometric transformations here
	if (axis == 1) {
		glRotatef(angle, 0, 1, 0);
	}
	else {
		glRotatef(angle, 0, 0, 1);
	}

	glTranslatef(X, 0, Z);

	// put drawing instructions here
	//drawpiram(-0.3, 0.3, 0.3, -0.3, .3, 0.3, -.3, -.3, 0, 0, 0.9);
	//glutWireTeapot(0.4);
	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events



// write function to process menu events



int main(int argc, char **argv) {
	int menus[10], mid = 0;
	for (int i = 0; i < 10; i++)
	{
		menus[i] = -1;
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


	// put here the definition of the menu 
	glutAddMenuEntry("Rotate 360 Clock", 1);
	glutAddMenuEntry("Rotate 360 non Clock", 2);
	glutAttachMenu(GLUT_LEFT_BUTTON);
	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}

