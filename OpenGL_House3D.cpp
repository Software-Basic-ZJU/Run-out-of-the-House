#include "House\Floor.h"
#include "Helpers\FPS.h"
#include "House\Wall\Wall.h"
#include "House\Wall\WallwithDoor.h"
#include "House\Bed.h"
#include "House\Table\Table.h"
#include "House\Table\RoundTable.h"
#include "House\Door\RotateDoor.h"
#include "House\Door\TransDoor.h"

float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

float eye[] = { 0, 5, 20 };
float center[] = { 0, 0, 0 };

GLint tableList = 0;

/*
//test

Cubic *cubic = new Cubic(1, 1, 3);
Sphere *sphere = new Sphere(1,100,100);
Cylinder *cylinder = new Cylinder(2,8);
Cone *cone = new Cone(1.5, 5, 100, 2, 2, 2);


// 棱柱(棱台)测试
GLfloat testBtm[][2] = {
	{ 2, 2 },
	{ 2, -2 },
	{0,0}
};
GLfloat testTop[][2] = {
	{ 3, 3 },
	{3,-3},
	{0,0}
};
Prism *prism = new Prism(testBtm, 3, 5, testTop ,30);

*/
Floor *flo = new Floor();
Wall *entryWall1 = new Wall(1, 20, -20, 0, 55);
Wall *entryWall2 = new Wall(1, 20, 0, 0, 55);

Wall *westWall = new Wall(1,90, -49.5, 0, 0);
Wall *northWall = new Wall(98, 1, 0, 0, -44.5);
Wall *eastWall = new Wall(1, 90, 49.5, 0, 0);
Wall *southWall = new Wall(50, 1, 24.5, 0, 44.5);

Wall *roomWall1 = new Wall(29, 1,-34.5,0,44.5);
Wall *roomWall2 = new Wall(29, 1, -34.5, 0, 15);
Wall *roomWall3 = new Wall(29, 1, -34.5, 0, -15);
Wall *roomWall4 = new Wall(1, 30, 10, 0, -30);

WallwithDoor *doorWall1 = new WallwithDoor(30.5, 1, 10, 15, -20, 0, 30, 90);
WallwithDoor *doorWall2 = new WallwithDoor(30.5, 1, 10, 15, -20, 0, 0, 90);
WallwithDoor *doorWall3 = new WallwithDoor(30.5, 1, 10, 15, -4.75, 0, -15);
WallwithDoor *entrance = new WallwithDoor(20, 1, 10, 15, -10, 0, 65);

Bed *bed1 = new Bed(15,8,2,-41.5,0,-10.5,180);
Bed *bed2 = new Bed(15,8,2,-41.5,0,40,180);

Table *table = new Table(8, 8, 5, 0, 0, -35);
RoundTable *roundTable = new RoundTable(6, 5, 30, 0, -15);

RotateDoor *rotateDoor1 = new RotateDoor(10.5, 15, 1, -20, 0, 30, 90);
RotateDoor *rotateDoor2 = new RotateDoor(10.5, 15, 1, -20, 0, 0, 90);
RotateDoor *rotateDoor3 = new RotateDoor(10.5, 15, 1, -4.5, 0, -15);

TransDoor *transDoor = new TransDoor(30, 20, 1, -20, 0, -30, 90);

//显示列表
GLint HouseList(){
	GLfloat coeff[] = { 0.2, 0, 0.2, 1.0 };
	GLfloat white[] = { 0, 0.5, 0.5, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, coeff);
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);

	//cubic->setPosition(0, 0, -4);
	//cubic->render();
	
	//sphere->setPosition(-1, -1, 0);
	//sphere->render();

	//cylinder->render();

	//cone->render();

	//prism->render();
	flo->render();
	entryWall1->render();
	entryWall2->render();

	northWall->render();
	westWall->render();
	eastWall->render();
	southWall->render();

	roomWall1->render();
	roomWall2->render();
	roomWall3->render();
	roomWall4->render();

	doorWall1->render();
	doorWall2->render();
	doorWall3->render();

	entrance->render();

	bed1->render();
	bed2->render();

	table->render();
	roundTable->render();

	glEndList();
	return lid;
}

void display() // This function draws a triangle with RGB colors
{
	rotateDoor1->render();
	rotateDoor2->render();
	rotateDoor3->render();

	transDoor->render();
	glCallList(tableList);		//显示列表
}

void reshape(int width, int height)
{

	wHeight = height;
	wWidth = width;

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
	//glFrustum(-3, 3, -3, 3, 3,100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'p': {break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }

	case 'a': {
				  eye[0] -= 1.0f;
				  center[0] -= 1.0f;
				  break;
	}
	case 'd': {
				  eye[0] += 1.0f;
				  center[0] += 1.0f;
				  break;
	}
	case 'w': {
				  eye[1] -= 1.0f;
				  //center[1] -= 0.2f;
				  break;
	}
	case 's': {
				  eye[1] += 1.0f;
				 // center[1] += 0.2f;
				  break;
	}
	case 'z': {
				  eye[2] -= 0.2f;
				  center[2] -= 0.2f;
				  break;
	}
	case 'c': {
				  eye[2] += 0.2f;
				  center[2] += 0.2f;
				  break;
	}
	case 'q':{
				 fRotate -= 1.0f;
				 break;
	}
	case 'e':{
				 fRotate += 1.0f;
				 break;
	}
	case 'r':{
				 if (rotateDoor1->getStatus()){
					 rotateDoor1->closeDoor();
				 }
				 else{
					 rotateDoor1->openDoor();
				 }
				 break;
	}
	case 't':{
				 if (transDoor->getStatus()){
					 transDoor->closeDoor();
				 }
				 else{
					 transDoor->openDoor();
				 }
				 break;
	}
	}

	
}


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,0,0)，Y轴向上

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5, 5, 5, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glScalef(0.2, 0.2, 0.2);
	display();						// Draw triangle

	if (bAnim) fRotate += 0.05f;

	FPS *fps = new FPS();
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(960, 600);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	tableList = HouseList();			//房间显示列表

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


