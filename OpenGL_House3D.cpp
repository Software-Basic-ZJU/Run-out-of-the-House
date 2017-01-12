#include "House\House.h"
#include "ScreenShot\ScreenShot.h"
#include "Helpers\alert.h"

int SCREEN_WIDTH = 960, SCREEN_HEIGHT = 600;
int ALERT = 0;	//0������ʾ��Ϣ	1�������ɹ�	2�����Կ��

float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bAnim = false;
bool bWire = false;
bool bfullscreen = false;     // ȫ����ʶ
bool getKey = false;
bool win = false;

int wHeight = 0;
int wWidth = 0;

GLint tableList = 0;

GLfloat theta = 0.0f;       //�����ƵĽǶ�
GLfloat viewUp = 0.0f;      //�������¿�
//test

Sphere *sphere;
Cylinder *cylinder;
Cone *cone[3];
Prism *prism;
Floor *flo;

Wall *entryWall1;
Wall *entryWall2;

Wall *westWall;
Wall *northWall;
Wall *eastWall;
Wall *southWall;

Wall *roomWall1;
Wall *roomWall2;
Wall *roomWall3;
Wall *roomWall4;

WallwithDoor *doorWall1;
WallwithDoor *doorWall2;
WallwithDoor *doorWall3;
WallwithDoor *entrance;

Table *table;
RoundTable *roundTable;
TransDoor *transDoor;

ElectricFan *fan;

GLTexture *doorTexture;
RotateDoor *rotateDoor1;
RotateDoor *rotateDoor2;
RotateDoor *rotateDoor3;

GLTexture* io_texture;
GLTexture* wall_texture;
GLTexture* door_text;
GLTexture* bed_text;
GLTexture* keyObj_text;
GLTexture* flower_text;
GLTexture* cone_text;

ImportObj* io;
ImportObj* door;
ImportObj* doorframe;
ImportObj* bed1;
ImportObj* bed2;
ImportObj* chair1;
ImportObj* chair2;
ImportObj* keyObj;
ImportObj* window;
ImportObj* sofa;

Light* light[4];//OpenGL���֧��8����Դ
alert *info = new alert();
int infotime = 0;

//��ʾ�б�
GLint HouseList(){
	GLfloat coeff[] = { 1.0, 0.95, 0.95, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, coeff);
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);

	//cubic->setPosition(0, 0, -4);
	//cubic->render();
	GLfloat spceu[] = { 1.0, 0.0, 0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spceu);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 35.0);
	sphere->render();

	cylinder->render();

	for (int i = 0; i < 3;i++)
		cone[i]->render();

	prism->render();

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

	table->render();
	roundTable->render();

	//io->draw();

	bed1->draw();
	bed2->draw();
	chair1->draw();

	window->draw();
	sofa->draw();

	glEndList();
	return lid;
}

void display() // This function draws a triangle with RGB colors
{
	rotateDoor1->render();
	rotateDoor2->render();
	rotateDoor3->render();

	if (!getKey) {
		keyObj->draw();
	}

	transDoor->render();

	fan->render();

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
//float eye[3] = { -2.0f, 20.0f, 13.8f };		//�ϵ��ӽ�
float eye[3] = { -2.0f, 1.2f, 11.8f };	//�����ӽ�
float center_next[3] = { -2.0f, 1.2f, 9.8f };
float eye_next[3] = { -2.0f, 1.2f, 11.8f };
GLfloat light_spo_pos[4] = { 0,6,0,1 };
GLfloat light_spo_dir[4] = { 0,-1,0,1 };
GLfloat light_spo_angle = 5;

void key(unsigned char k, int x, int y)
{

	switch (k)
	{
	case 27:
	//case 'q': {exit(0); break; } //�˳�  

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
		center[1] += 0.4f;

		break;
	}
	case 'k': {//�ӽ�����  
		center_next[1] -= 0.4f;
		center[1] -= 0.4f;

		break;
	}

		//����Ϊ�ϵ��ӽǵĲ�����������������Ķ�λ���ԣ��������������ע�͵�
	case 't':{	//����
				 eye[1] += 0.4f;
				 center[1] += 0.4f;
				 break;
	}
	case 'g':{	//���
				 eye[1] -= 0.4f;
				 center[1] -= 0.4f;
				 break;
	}
	case 'y':{  //̧ͷ��
				 center[1] += 0.4f;
				 break;
	}
	case 'h':{	//��ͷ��
				 center[1] -= 0.4f;
				 break;
	}
	case 'p': case 'P': {
		SaveScreenShot();
		ALERT = 1;
		break;
	}
	//case 'm':{	//���Ų���
	//			 if (rotateDoor3->getStatus()){
	//				 rotateDoor3->closeDoor();
	//			 }
	//			 else
	//				 rotateDoor3->openDoor();
	//			 break;
	//}
	case ' ': {
		point e(5.0*eye[0], -5 * eye[2] + 5.0), c(5.0*center[0], -5 * center[2] + 5.0);
		int opendoor = nearDoor(e, c);

		switch (opendoor) {
		case 1: {
			printf("door1\n");
			bool isopen = rotateDoor1->getStatus();
			if (isopen) {
				rotateDoor1->closeDoor();
			}
			else
			{
				rotateDoor1->openDoor();
			}
			break;
		}
		case 2: {
			printf("door2\n");
			bool isopen = rotateDoor2->getStatus();
			if (isopen) {
				rotateDoor2->closeDoor();
			}
			else
			{
				rotateDoor2->openDoor();
			}
			break;
		}
		case 3: {
			printf("door3\n");
			bool isopen = rotateDoor3->getStatus();
			if (isopen) {
				rotateDoor3->closeDoor();
			}
			else
			{
				rotateDoor3->openDoor();
			}
			break;
		}
		case 4: {
			printf("door4\n");
			bool isopen = transDoor->getStatus();
			if (isopen) {
				transDoor->closeDoor();
			}
			else
			{
				transDoor->openDoor();
			}
			break;
		}
		case 5:
		{
			printf("fetching key\n");
			if (!getKey) {
				ALERT = 2;
				getKey = true;
			}
			break;
		}
		case 6:
		{
			printf("win!\n");
			if (!win)
			{
				ALERT = 3;
				win = true;

			}
			break;
		}
		default:
		{
			break;
		}
		}

		break;
	}
	case 'f': case 'F': {
		if (bfullscreen)
		{
			SCREEN_WIDTH = 960;
			SCREEN_HEIGHT = 600;
			glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
			glutPositionWindow(100, 100);
		}
		else
		{
			SCREEN_WIDTH = 1280;
			SCREEN_HEIGHT = 1024;
			glutFullScreen();
		}
	
		bfullscreen = !bfullscreen;
		break;
	}
	}

	//��ǽ�ڵ���ײ���  
	//point p1(-30, -30), p2(30, 30);
	if (!CollosionTest(5.0*eye_next[0], -5 * eye_next[2]+5.0, rotateDoor1->getStatus(), rotateDoor2->getStatus(), rotateDoor3->getStatus(), transDoor->getStatus(), getKey)) {
		center[0] = center_next[0];
		//center[1] = center_next[1];
		center[2] = center_next[2];
		eye[0] = eye_next[0];
		//eye[1] = eye_next[1];
		eye[2] = eye_next[2];
	}
	else {
		center_next[0] = center[0];
		//center_next[1] = center[1];
		center_next[2] = center[2];
		eye_next[0] = eye[0];
		//eye_next[1] = eye[1];
		eye_next[2] = eye[2];
	}
	////////////////////////////
	if(myRoonNo(5.0*eye[0], -5 * eye[2] + 5.0) == 20)
	{
		printf("win!\n");
		if (!win)
		{
			ALERT = 3;
			win = true;

		}
	}
	printf("%f  %f\n", 5.0*eye[0], -5 * eye[2] + 5.0);
}

/*��ײ����һЩСbug����ע��������
void SetViewByMouse()
{
POINT mousePos;              //���λ��
POINT middlePos;             //��Ļ����λ��
middlePos.x = SCREEN_WIDTH / 2; // SCREEN_WIDHT Ϊ��Ļ��ȣ�ȫ�ֱ������ɸġ�
middlePos.y = SCREEN_HEIGHT / 2;

GetCursorPos(&mousePos);      //�õ���굱ǰλ��

if (mousePos.x == middlePos.x&&mousePos.y == middlePos.y)    //������û�ж������ء�
return;
SetCursorPos(middlePos.x, middlePos.y);                 //�����궯�ˣ���ָ�����Ļ����
theta += GLfloat(-middlePos.x + mousePos.x) / 500;      //��ת�ı���
viewUp += GLfloat(middlePos.y - mousePos.y) / 500;     //���¸ı���
}
*/

void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//SetViewByMouse();

	/*
	if (theta>360) theta = 0.0f; //�ǶȲ��ܴ���360
	if (viewUp> 0.5f)	viewUp = 0.5f;         //�����ӽ�
	if (viewUp<-0.6f)	viewUp = -0.6f;
	center[0] = float(eye[0] + cos(theta));
	center[2] = float(eye[2] + sin(theta));
	center[1] = eye[1];
	*/

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// ������0��0��0�����ӵ����� (0,0,0)��Y������
	glutPostRedisplay();

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

    //light[0]�Ƿ����Թ�Դ
    light[0] = new Light(GL_LIGHT0); 
    light[0]->setPosition(5, 5, 5);
    light[0]->setColor(0.8, 0.8, 0.8, 0.1);
    light[0]->setAmbientLight();
    light[0]->setDiffuseLight();
    light[0]->enable();

    //light[1]��λ���Թ�Դ�����Դ������������Կ���ʹ��λ���Թ�Դ
    light[1] = new Light(GL_LIGHT1);
    light[1]->setPosition(0, 10, 0, 1);
    light[1]->setColor(1, 1, 1, 1);
    light[1]->setDiffuseLight();
    light[1]->enable();

    //light[2]��λ���Թ�Դ�����Դ���۹�ƣ� ����һЩ���⡣
    light[2] = new Light(GL_LIGHT2);
	light[2]->setPosition(eye[0], eye[1], eye[2], 1);//�����˵�λ�����þ۹�Ƶ�λ��
    light[2]->setColor(1, 1, 1, 1);
    light[2]->setDiffuseLight();
    light[2]->setAgglomeration(100);
    light[2]->setSpotangle(45);
    light[2]->setLightDir(center[0], center[1], center[2]);//�����˵ĳ������þ۹�Ƶĳ���
    light[2]->setLimitRange();
    light[2]->enable();

	//light[3]�Ǿ����
	light[3] = new Light(GL_LIGHT3);
	light[3]->setPosition(0, 10, 0);
	light[3]->setColor(1, 1, 1, 1);
	light[3]->setSpecular();
	light[3]->enable();

	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glScalef(0.2, 0.2, 0.2);
	display();						// Draw triangle

	if (bAnim) fRotate += 0.05f;

	FPS *fps = new FPS();
	if (ALERT == 1) {
		(*info).display("Screen Shot Success!");
		infotime++;
		if (infotime > 40) {
			ALERT = 0;
		}
	}
	else if (ALERT == 2) {
		(*info).display("Get A Key!");
		infotime++;
		if (infotime > 40) {
			ALERT = 0;
		}
	}
	else if (ALERT == 3) {
		(*info).display("You Win!");
		infotime++;
		if (infotime > 40) {
			ALERT = 0;
		}
	}
	else {
		infotime = 0;
	}
	glLoadIdentity();
	glFlush();
	glutSwapBuffers();
}

void objectInit() {
	io_texture = new GLTexture;
	io_texture->Load("Data/wood2.bmp");

	wall_texture = new GLTexture;
	wall_texture->Load("Data/6.bmp");

	//�ذ�
	flo = new Floor();
	flo->setMainTexture(io_texture);
	flo->setEntryTexture(io_texture);

	entryWall1 = new Wall(1, 20, -20, 0, 55);
	entryWall2 = new Wall(1, 20, 0, 0, 55);
	entryWall1->setTexture(wall_texture);
	entryWall2->setTexture(wall_texture);

	//���ӵ���Χǽ
	westWall = new Wall(1, 90, -49.5, 0, 0);
	northWall = new Wall(98, 1, 0, 0, -44.5);
	eastWall = new Wall(1, 90, 49.5, 0, 0);
	southWall = new Wall(50, 1, 24.5, 0, 44.5);
	westWall->setTexture(wall_texture);
	eastWall->setTexture(wall_texture);
	northWall->setTexture(wall_texture);
	southWall->setTexture(wall_texture);

	//���������ǽ
	roomWall1 = new Wall(29, 1, -34.5, 0, 44.5);
	roomWall2 = new Wall(29, 1, -34.5, 0, 15);
	roomWall3 = new Wall(29, 1, -34.5, 0, -15);
	roomWall4 = new Wall(1, 30, 10, 0, -30);

	roomWall1->setTexture(wall_texture);
	roomWall2->setTexture(wall_texture);
	roomWall3->setTexture(wall_texture);
	roomWall4->setTexture(wall_texture);


	//���ŵ�ǽ
	doorWall1 = new WallwithDoor(30.5, 1, 10, 15, -20, 0, 30, 90);
	doorWall2 = new WallwithDoor(30.5, 1, 10, 15, -20, 0, 0, 90);
	doorWall3 = new WallwithDoor(30.5, 1, 10, 15, -4.75, 0, -15);
	entrance = new WallwithDoor(20, 1, 10, 15, -10, 0, 65);
	doorWall1->setTexture(wall_texture);
	doorWall2->setTexture(wall_texture);
	doorWall3->setTexture(wall_texture);
	entrance->setTexture(wall_texture);

	//���ּҾ�

	table = new Table(8, 8, 5, 0, 0, -35);
	roundTable = new RoundTable(6, 5, 30, 0, -15);
	transDoor = new TransDoor(30, 20, 1, -20, 0, -30, 90);

	flower_text = new GLTexture;
	flower_text->Load("data/flower.bmp");
	chair1 = new ImportObj("data/chair2.obj");
	chair1->setTexture(flower_text);
	chair1->setPosition(20, 0, -15);
	chair1->setScalef(0.01, 0.01, 0.01);
	chair1->setRotatef(90, 0, 1, 0);

	table->setTexture(flower_text);
	roundTable->setTexuture(flower_text);
	GLTexture *transDoorText = new GLTexture;
	transDoorText->Load("data/feather.bmp");
	transDoor->setTexture(transDoorText);

	//��,�����={21.03,16.15,7.82} ��С֮��
	bed_text = new GLTexture;
	bed_text->Load("data/wood3.bmp");

	bed1 = new ImportObj("data/bed.obj");
	bed1->setTexture(bed_text);
	bed1->setScalef(0.01, 0.01, 0.01);
	bed1->setPosition(-41, 0, 26);

	bed2 = new ImportObj("data/bed1.obj");
	bed2->setTexture(flower_text);
	bed2->setScalef(0.005, 0.005, 0.005);
	bed2->setPosition(-40.5, 0, -7);

	//Կ�׳���� 937mm 100mm 466mm δ����
	keyObj_text = new GLTexture;
	keyObj_text->Load("data/13.bmp");

	keyObj = new ImportObj("data/key.obj");
	keyObj->setTexture(keyObj_text);
	keyObj->setScalef(0.05, 0.05, 0.05);
	keyObj->setPosition(-44, 4, -35);

	//��ת��
	doorTexture = new GLTexture;
	doorTexture->Load("Data/wood2.bmp");
	rotateDoor1 = new RotateDoor("Data/door1.obj",doorTexture, 13.5, 13, 1, -20, 0, 30, 90);
	rotateDoor2 = new RotateDoor("Data/door1.obj",doorTexture, 13.5, 13, 1, -20, 0, 0, 90);
	rotateDoor3 = new RotateDoor("Data/door1.obj",doorTexture, 13.5, 13, 1, -4.5, 0, -15,0);

	//���ּ�����
	sphere = new Sphere(1, 150, 150, 25, 6.5, -15);			//����
	sphere->setTexture(wall_texture);
	// ����(��̨)
	GLfloat TopFace[][2] = {
		{ 2, 0 },
		{ 0, -3 },
		{ -2, 0 },
		{ -1, 1 },
		{ 1, 1 }
	};
	GLfloat BtmFace[][2] = {
		{ 3, 0 },
		{ 0, -4 },
		{ -3, 0 },
		{ -1.5, 1.5 },
		{ 2, 2 }
	};
	prism = new Prism(BtmFace, 5, 5, TopFace, 30, 30, 40, 0, 10);
	prism->rotateY(-60);
	prism->setTexture(bed_text);

	cylinder = new Cylinder(2, 4, 200, 30, 2, -6);
	cylinder->setTexture(flower_text);
	
	cone_text = new GLTexture();
	cone_text->Load("data/flower3.bmp");
	cone[0] = new Cone(1.5, 3, 300, -5, 17.5, -15);
	cone[0]->rotateX(90);
	cone[1] = new Cone(1.5, 3, 300, -20, 17.5, 0);
	cone[1]->rotateZ(-90);
	cone[2] = new Cone(1.5, 3, 300, -20, 17.5, 30);
	cone[2]->rotateZ(-90);
	for (int i = 0; i < 3; i++)
		cone[i]->setTexture(cone_text);

	//�����
	fan = new ElectricFan(2, 1, 30, 18, -15);
	fan->open();

	//����
	window = new ImportObj("data/window2.obj");
	window->setScalef(0.01, 0.01, 0.01);
	window->setTexture(flower_text);
	window->setRotatef(-90, 0, 1, 0);
	window->setPosition(47, 2.5, 25);

	//ɳ��
	sofa = new ImportObj("data/Sofa.obj");
	sofa->setScalef(0.2, 0.2, 0.2);
	sofa->setTexture(flower_text);
	sofa->setRotatef(90, 0, 1, 0);
	sofa->setPosition(-43, 0, -32);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	objectInit();

	tableList = HouseList();			//������ʾ�б�

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


