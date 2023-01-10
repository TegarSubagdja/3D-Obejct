//Tegar Subagdja
#include <fstream>
#include <math.h>
#include <time.h>
#include <vector>

#include <GL/freeglut.h>
#include <GL/glext.h>

#include "../Library/loadpng.h"
#include "../Library/process_image.h"
#include "../Library/gl_texture.h"

#define WIDTH 600
#define HEIGHT 600

void init () {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_pos[] = {-1.0f, 10.0f, 100.0f,1.0f};
	glLightfv(GL_LIGHT0,GL_POSITION, light_pos);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, 1.0, 1.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	float v[8][3] = {{-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},
					 {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}};
	float n[6][3] = {{0, 0, -1}, {0, 0, 1}, {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}};
	int f_v[6][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {0, 4, 7, 3}, {1, 5, 6, 2}, {0, 1, 5, 4}, {3, 2, 6, 7}};
	int f_n[6] = {0, 1, 2, 3, 4, 5};
	glTranslatef(30.0f, 0.0f, -20.0f);
	glRotatef(30.0f, 1.0f, -1.0f, 0.0f);
	for (int i = 0; i < 6; i++) {
		glBegin(GL_POLYGON);
		glNormal3fv(n[f_n[i]]);
		glVertex3fv(n[f_v[i][0]]);
		glVertex3fv(n[f_v[i][1]]);
		glVertex3fv(n[f_v[i][2]]);
		glVertex3fv(n[f_v[i][3]]);
	}
	glutSwapBuffers();
}

int main (int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
	glutSetOption(GLUT_MULTISAMPLE,8);
	int POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
	int POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
	glutInitWindowPosition(POS_X, POS_Y);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Load Model");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
