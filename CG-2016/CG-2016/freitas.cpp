#include <GL/glut.h>
#include <math.h>

float x = 0, y = 0, z = 0;
int angle = 0;

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
	gluLookAt(0.0, 6.0, 1.0,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	// put the geometric transformations here
	glTranslatef(x, y, z);
	glRotatef(angle, 0, 1, 0);

	// put drawing instructions here
	glBegin(GL_TRIANGLES);

	//base
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);

	
	glEnd();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events

void responseKeyboard(unsigned char key, int x, int y) {
}

void responseKeyboardSpecial(int key_code, int x1, int y1) {

	switch (key_code)
	{
	case GLUT_KEY_UP: y++; break;
	case GLUT_KEY_DOWN: y--; break;
	case GLUT_KEY_LEFT: x--; break;
	case GLUT_KEY_RIGHT: x++; break;
	case GLUT_KEY_F1: angle++; break;
	case GLUT_KEY_F2: angle--; break;
	default:
		break;
	}
	glutPostRedisplay();
}

// write function to process menu events




int main(int argc, char **argv) {

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
