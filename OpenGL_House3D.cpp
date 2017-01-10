#include "Geometry\Sphere.h"
#include "House\Floor.h"
#include "Helpers\FPS.h"
#include "House\Wall\Wall.h"
#include "House\Wall\WallwithDoor.h"
#include "House\Bed.h"
#include "House\Table\Table.h"
#include "House\Table\RoundTable.h"
#include "House\Door\RotateDoor.h"
#include "House\Door\TransDoor.h"

#include "Model\ImportObj.h"

#include "Bump\Person.h"
float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

//float eye[] = { 0, 5, 20 };
//float center[] = { 0, 0, 0 };

GLint tableList = 0;


//test

//Cubic *cubic = new Cubic(1, 1, 3);
Sphere *sphere = new Sphere(1,100,100);
//Cylinder *cylinder = new Cylinder(2,8,200);
//Cone *cone = new Cone(1.5, 5, 100, 2, 2, 2);


// ����(��̨)����
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
//Prism *prism = new Prism(testBtm, 3, 5, testTop ,30);


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

GLTexture *io_texture;
GLTexture *wall_texture;

ImportObj*io;

//��ʾ�б�
GLint HouseList(){
	GLfloat coeff[] = { 1.0, 0.8, 0.5, 1.0 };
	GLfloat white[] = { 0, 0.5, 0.5, 1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, coeff);
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);

	//cubic->setPosition(0, 0, -4);
	//cubic->render();
	
	sphere->setPosition(0, 2, 0);
	sphere->render();

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

	//io->draw();

	glEndList();
	return lid;
}

void display() // This function draws a triangle with RGB colors
{
	rotateDoor1->render();
	rotateDoor2->render();
	rotateDoor3->render();

	transDoor->render();
	glCallList(tableList);		//��ʾ�б�
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

float center[3] = { -2.0f, 1.2f, 9.8f };
float eye[3] = { -2.0f, 1.2f, 13.8f };
float center_next[3] = { -2.0f, 1.2f, 9.8f };
float eye_next[3] = { -2.0f, 1.2f, 13.8f };
GLfloat light_spo_pos[4] = { 0,6,0,1 };
GLfloat light_spo_dir[4] = { 0,-1,0,1 };
GLfloat light_spo_angle = 5;

void key(unsigned char k, int x, int y)
{

	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; } //�˳�  

	case 'a': { //����  
		move(eye, center, eye_next, center_next, left_ward);
		break;
	}
	case 'd': { //����  
		move(eye, center, eye_next, center_next, right_ward);
		break;
	}
	case 'w': { //ǰ��  
		move(eye, center, eye_next, center_next, front);
		break;
	}
	case 's': {  //����  
		move(eye, center, eye_next, center_next, back);
		break;
	}

	case 'j': {//�ӽ�����  
		rotate(eye, center, eye_next, center_next, left_ward);
		break;
	}
	case 'l': {//�ӽ�����  
		rotate(eye, center, eye_next, center_next, right_ward);
		break;
	}
	case 'i': {//�ӽ�����  
		center_next[1] += 0.4f;
		break;
	}
	case 'k': {//�ӽ�����  
		center_next[1] -= 0.4f;
		break;
	}

	}
	//��ǽ�ڵ���ײ���  
	//point p1(-30, -30), p2(30, 30);
	if (!CollosionTest(5.0*eye_next[0], -5 * eye_next[2]+5.0, rotateDoor1->getStatus(), rotateDoor2->getStatus(), rotateDoor3->getStatus(), transDoor->getStatus())) {
		center[0] = center_next[0];
		center[1] = center_next[1];
		center[2] = center_next[2];
		eye[0] = eye_next[0];
		eye[1] = eye_next[1];
		eye[2] = eye_next[2];
	}
	else {
		center_next[0] = center[0];
		center_next[1] = center[1];
		center_next[2] = center[2];
		eye_next[0] = eye[0];
		eye_next[1] = eye[1];
		eye_next[2] = eye[2];
	}
	printf("%f  %f\n", 5.0*eye[0], -5 * eye[2] + 5.0);
}


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// ������0��0��0�����ӵ����� (0,0,0)��Y������

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

	io_texture = new GLTexture;
	io_texture->Load("Data/Crack.bmp");

	wall_texture = new GLTexture;
	wall_texture->Load("Data/black_white.bmp");

	io = new ImportObj("Data/door2.obj");
	io->setTexture(io_texture);
	io->setTranslatef(2, 3, 3);
	io->setScalef(1, 1, 1);

	flo->setMainTexture(io_texture);

	rotateDoor1->setTexture(wall_texture);
	rotateDoor2->setTexture(wall_texture);
	rotateDoor3->setTexture(wall_texture);

	westWall->setTexture(io_texture);
	eastWall->setTexture(io_texture);
	northWall->setTexture(io_texture);
	southWall->setTexture(io_texture);

	sphere->setTexture(io_texture);

	tableList = HouseList();			//������ʾ�б�

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


