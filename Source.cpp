#include <cmath>
#include <iostream>
#include <GL/glut.h>

using namespace std;

int is_depth;

double deg = 0, lrot = 0;
double dist = 15, twist = -5, elev = 0, azim = 80;
double camz = 10, thet = -.1;
double atx = 0, aty = 0, atz = 0;
double arrays[16];
float lightx = 0, lighty = 2.5, lightz = 0;
float light_position[] = { -4, -3, 4, 0.0 };
float spinx = 0, spiny = 0, spinz = 0;
float pos[] = { -4, -3, 4, 1 };

char at = '1';
void display();


void renderBitmapString(float x, float y, float z, void* font, const char* string)
{
	const char* c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void flyView(GLdouble dist, GLdouble twist, GLdouble elev, GLdouble azim) {
	glTranslated(0.0, 0.0, -dist);
	glRotated(-twist, 0.0, 0.0, 1.0);
	glRotated(-elev, 1.0, 0.0, 0.0);
	glRotated(azim, 0.0, 0.0, 1.0);
}

void keyboard(unsigned char key, int x, int y) {
	if (key >= '1' && key <= '7') {
		at = key;
	}
	switch (key) {
	case 'w': case 'W':
		std::cout << arrays[((at - '0') - 1) * 3] << "\n";
		if ((arrays[((at - '0') - 1) * 3]) > -90)
			arrays[((at - '0') - 1) * 3] -= 1;
		break;
	case 's': case 'S':if (arrays[((at - '0') - 1) * 3] < 90) arrays[((at - '0') - 1) * 3] += 1;  break;
	case 'c': case 'C':arrays[(((at - '0') - 1) * 3 + 1)] += 1;  break;
	case 'z': case 'Z':arrays[(((at - '0') - 1) * 3 + 1)] -= 1;  break;
	case 'd': case 'D':arrays[(((at - '0') - 1) * 3 + 2)] -= 1;  break;
	case 'a': case 'A':arrays[(((at - '0') - 1) * 3 + 2)] += 1; break;

	case 'I': case 'i':spinx += 5; break;
	case 'O': case 'o':spiny += 5; break;
	case 'P': case 'p':spinz += 5; break;

	case 't':
		static bool on_off = true;
		if (on_off) { glDisable(GL_LIGHT0); on_off = false; }
		else { glEnable(GL_LIGHT0); on_off = true; }
		break;
	}
	glutPostRedisplay();
}
void point_source() {

	GLfloat light_ambient[] = { 20.0, 60.0, 20.0, 1.0 };
	GLfloat light_diffuse[] = { 90.0, 90.0, 90.0, 1.0 };
	GLfloat light_specular[] = { 200.0, 200.0,200.0, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };


	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);

	glEnable(GL_LIGHT0);
}

void spot_light() {
	GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light1_diffuse[] = { 20.0,  20.0,  20.0, 1.0 };
	GLfloat light1_specular[] = { 20.0,  20.0,  20.0, 1.0 };
	GLfloat light1_position[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat spot_direction[] = { -1.0, -1.0, -10.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 80.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

	glEnable(GL_LIGHT1);
}

void mat_cube1() {

	GLfloat mat_ambient[] = { .1, .1, .1, 1.0 };
	GLfloat mat_specular[] = { 0.5, 0, 0, 1.0 };
	GLfloat mat_diffuse[] = { 0.7, 0.2, 0.2, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void mat_cube2() {

	GLfloat mat_ambient[] = { .1, .1, .1, 1.0 };
	GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.0, 0.8, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void mat_sph1() {

	GLfloat mat_ambient[] = { .1, .1, .1, 1.0 };
	GLfloat mat_specular[] = { 0.0, 0.5, 0.5, 1.0 };
	GLfloat mat_diffuse[] = { 0.0, 0.8, 0.8, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void mat_floar() {
	GLfloat mat_ambient[] = { .1, .1, .1, 1.0 };
	GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}



void spinSphere() {
	deg += 4;
	glutPostRedisplay();
}

void timer_func(int n) {
	int delay = 50;
	spinSphere();
	glutTimerFunc(delay, timer_func, 0); // recursively call timer_func
}



void display(void) {
	float lp[4]; lp[0] = 0; lp[1] = -3; lp[2] = 5; lp[3] = 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    glLoadIdentity();
	     flyView(15, 0, 80, -5);
		  glPushMatrix();
		   glRotated(spinx, 1.0, 0.0, 0.0);
			glRotated(spiny, 0.0, 1.0, 0.0);
			 glRotated(spinz, 0.0, 0.0, 1.0);
	        glTranslatef(0, 0, 10);
	       glLightfv(GL_LIGHT0, GL_POSITION, lp);
	      glDisable(GL_LIGHTING);
	     glDisable(GL_LIGHT0);
	    glColor3f(1, 1, 0);
	   glutSolidSphere(.5, 20, 20);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPopMatrix();

	//draw the sphere

	glPushMatrix();
	mat_floar();

	glBegin(GL_QUADS);

	glNormal3f(-1, 0,  1);
	glVertex3f(-8.0, -8.0, 0.0);
	glNormal3f(-1, 0,  1);
	glVertex3f(-8.0, 8.0, 0.0);
	glNormal3f(1, 0, 1);
	glVertex3f(8.0, 8.0, 0.0);
	glNormal3f(-1, 0, 1);
	glVertex3f(8.0, -8.0, 0.0);

	glEnd();

	glPopMatrix();

	glDisable(GL_LIGHTING);
	// Transform the camera 
	renderBitmapString(-21, 10, 15, (void*)GLUT_BITMAP_9_BY_15, "W-S around x-axis");
	renderBitmapString(-21, 10, 13, (void*)GLUT_BITMAP_9_BY_15, "A-D around z-axis");
	renderBitmapString(-21, 10, 11, (void*)GLUT_BITMAP_9_BY_15, "Z-C around y-axis");
	renderBitmapString(-22, 10, 9, (void*)GLUT_BITMAP_9_BY_15, "1-5 switch between joins");
	renderBitmapString(-22, 10, 7, (void*)GLUT_BITMAP_9_BY_15, "i,o,p to controll the sun");
	renderBitmapString(0, 10, 13, (void*)GLUT_BITMAP_9_BY_15, "X");
	renderBitmapString(-5, 10, 16, (void*)GLUT_BITMAP_9_BY_15, "Z");
	renderBitmapString(-5, 20, 16, (void*)GLUT_BITMAP_9_BY_15, "Y");

	glBegin(GL_LINES);

	glVertex3f(-10, 10, 13);
	glVertex3f(0, 10, 13);

	glColor3f(0, 0, 1);
	glVertex3f(-5, 10, 16);
	glVertex3f(-5, 10, 10);
	glColor3f(0, 1, 0);
	glVertex3f(-5, 20, 16);
	glColor3f(0, 0, 1);

	glVertex3f(-5, 0, 10);
	glEnd();
	glEnable(GL_LIGHTING);
	// Move the LIGHT0 source if user click key "m" and "n"

	mat_cube1();

	glPushMatrix();

	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(0, -7, .2);
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHTING);

	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 0.4f, 0.4f, .15, 32, 32);

	glRotatef(arrays[2], 0, 0, 1);
	glRotatef(arrays[0], 1, 0, 0);
	glRotatef(arrays[1], 0, 1, 0);
	glColor3f(0.0, 1.0, 1.0);
	gluCylinder(quadratic, 0.2f, 0.2f, 1, 32, 32);

	glTranslatef(0, 0.2, 1.2);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadratic, 0.3f, 0.3f, .5, 32, 32);
	gluDisk(quadratic, 0.0, 0.3, 64, 1);

	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	gluDisk(quadratic, 0.0, 0.3, 64, 1);
	glPopMatrix();

	glTranslatef(0, 0.3, 0.3);
	glRotatef(arrays[5], 0, 0, 1);
	glRotatef(arrays[3], 1, 0, 0);
	glRotatef(arrays[4], 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(10, 0, 1, 0);
	gluCylinder(quadratic, 0.2f, 0.2f, 1.5, 32, 32);

	glTranslatef(0, 0.25, 1.7);
	glRotatef(90, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	gluDisk(quadratic, 0.0, 0.3, 64, 1);
	glPopMatrix();

	gluCylinder(quadratic, 0.3f, 0.3f, .5, 32, 32);
	gluDisk(quadratic, 0.0, 0.3, 64, 1);

	glTranslatef(0, -0.05, 0.2);
	glRotatef(arrays[8], 0, 0, 1);
	glRotatef(arrays[6], 1, 0, 0);
	glRotatef(arrays[7], 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(55, 0, 1, 0);
	gluCylinder(quadratic, 0.2f, 0.2f, 2, 32, 32);
	mat_sph1();
	glTranslatef(0, .3, 2);
	glRotatef(-55, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadratic, 0.3f, 0.3f, .5, 32, 32);
	gluDisk(quadratic, 0.0, 0.3, 64, 1);

	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	gluDisk(quadratic, 0.0, 0.3, 64, 1);
	glPopMatrix();

	glTranslatef(0, -0.05, 0.2);
	glRotatef(arrays[11], 0, 0, 1);
	glRotatef(arrays[9], 1, 0, 0);
	glRotatef(arrays[10], 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(30, 0, 1, 0);
	gluCylinder(quadratic, 0.2f, 0.2f, 1, 32, 32);


	mat_cube2();

	glTranslatef(0, 0, 1.2);
	glutSolidSphere(0.3, 10, 10);
	glRotatef(60, 0, 1, 0);
	glRotatef(arrays[14], 0, 0, 1);
	glRotatef(arrays[12], 1, 0, 0);
	glRotatef(arrays[13], 0, 1, 0);
	gluCylinder(quadratic, 0.13f, 0.13f, 1.5, 32, 32);
	glRotatef(arrays[14], 0, 0, 1);
	glRotatef(arrays[12], 1, 0, 0);
	glRotatef(arrays[13], 0, 1, 0);
	glRotatef(-100, 0, 1, 0);
	gluCylinder(quadratic, 0.13f, 0.13f, 1.5, 32, 32);

	glPopMatrix();
	glutSwapBuffers();
}
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);
	//point_source();
	point_source();

	glEnable(GL_DEPTH_TEST); // enable depth test 
	glShadeModel(GL_SMOOTH);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10.0, 10.0, -10.0, 10.0, -30, 30.0);
	gluPerspective(80, w / h, 2, 40);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutTimerFunc(5, timer_func, 0);
	glutMainLoop();
	return 0;
}