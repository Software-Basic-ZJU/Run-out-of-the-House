#include "House\House.h"
#include "ScreenShot\ScreenShot.h"
#include "Helpers\alert.h"

int SCREEN_WIDTH = 960, SCREEN_HEIGHT = 600;
int ALERT = 0;	//0：无显示信息	1：截屏成功	2：获得钥匙 3:成功逃脱
bool getKey = false;		//是否拿到钥匙

float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bAnim = false;
bool bWire = false;
bool bfullscreen = false;     // 全屏标识

int wHeight = 0;
int wWidth = 0;

//float eye[] = { 0, 5, 20 };
//float center[] = { 0, 0, 0 };

GLint tableList = 0;

GLfloat theta = 0.0f;       //鼠标控制的角度
GLfloat viewUp = 0.0f;      //向上向下看
//test

//Cubic *cubic = new Cubic(1, 1, 3);
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
RotateDoor *rotateDoor4;

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

Light* light[4];//OpenGL最多支持8个光源

//显示提示信息
alert *info = new alert();
int infotime = 0;

//显示列表
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
	rotateDoor4->render();

	glEndList();
	return lid;
}

void display() // This function draws a triangle with RGB colors
{
	rotateDoor1->render();
	rotateDoor2->render();
	rotateDoor3->render();

	transDoor->render();

	fan->render();

	if (!getKey){
		keyObj->draw();
	}

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

float center[3] = { -2.0f, 1.2f, 9.8f };
//float eye[3] = { -2.0f, 20.0f, 13.8f };		//上帝视角
float eye[3] = { -2.0f, 1.2f, 11.8f };	//漫游视角
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
	//case 'q': {exit(0); break; } //退出  

	case 'a': { //左移  
		move(eye, center, eye_next, center_next, left_ward);
		break;
	}
	case 'd': { //右移  
		move(eye, center, eye_next, center_next, right_ward);
		break;
	}
	case 'w': { //前移  
		move(eye, center, eye_next, center_next, front);
		break;
	}
	case 's': {  //后移  
		move(eye, center, eye_next, center_next, back);
		break;
	}

	case 'j': {//视角左移  
		rotate(eye, center, eye_next, center_next, left_ward);
		break;
	}
	case 'l': {//视角右移  
		rotate(eye, center, eye_next, center_next, right_ward);
		break;
	}
	case 'i': {//视角上移  
		center_next[1] += 0.4f;
		center[1] += 0.4f;

		break;
	}
	case 'k': {//视角上移  
		center_next[1] -= 0.4f;
		center[1] -= 0.4f;

		break;
	}

		//以下为上帝视角的操作，方便做几何体的定位调试，如果测试漫游请注释掉
	case 't':{	//飞天
				 eye[1] += 0.4f;
				 center[1] += 0.4f;
				 break;
	}
	case 'g':{	//落地
				 eye[1] -= 0.4f;
				 center[1] -= 0.4f;
				 break;
	}
	case 'y':{  //抬头看
				 center[1] += 0.4f;
				 break;
	}
	case 'h':{	//低头看
				 center[1] -= 0.4f;
				 break;
	}
	case 'm':{	//开门测试
				 if (rotateDoor3->getStatus()){
					 rotateDoor3->closeDoor();
				 }
				 else
					 rotateDoor3->openDoor();
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

	case 'p': case 'P': {
		SaveScreenShot();
		ALERT = 1;
		break;
	}
	}

	//与墙壁的碰撞检测  
	//point p1(-30, -30), p2(30, 30);
	if (!CollosionTest(5.0*eye_next[0], -5 * eye_next[2]+5.0, rotateDoor1->getStatus(), rotateDoor2->getStatus(), rotateDoor3->getStatus(), transDoor->getStatus())) {
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
	printf("%f  %f\n", 5.0*eye[0], -5 * eye[2] + 5.0);
}

/*碰撞会有一些小bug，先注释起来。
void SetViewByMouse()
{
POINT mousePos;              //鼠标位置
POINT middlePos;             //屏幕中心位置
middlePos.x = SCREEN_WIDTH / 2; // SCREEN_WIDHT 为屏幕宽度，全局变量，可改。
middlePos.y = SCREEN_HEIGHT / 2;

GetCursorPos(&mousePos);      //得到鼠标当前位置

if (mousePos.x == middlePos.x&&mousePos.y == middlePos.y)    //如果鼠标没有动，返回。
return;
SetCursorPos(middlePos.x, middlePos.y);                 //如果鼠标动了，则恢复到屏幕中心
theta += GLfloat(-middlePos.x + mousePos.x) / 500;      //旋转改变量
viewUp += GLfloat(middlePos.y - mousePos.y) / 500;     //上下改变量
}
*/

void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//SetViewByMouse();

	/*
	if (theta>360) theta = 0.0f; //角度不能大于360
	if (viewUp> 0.5f)	viewUp = 0.5f;         //限制视角
	if (viewUp<-0.6f)	viewUp = -0.6f;
	center[0] = float(eye[0] + cos(theta));
	center[2] = float(eye[2] + sin(theta));
	center[1] = eye[1];
	*/

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,0,0)，Y轴向上
	glutPostRedisplay();

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

    //light[0]是方向性光源
    light[0] = new Light(GL_LIGHT0); 
    light[0]->setPosition(5, 5, 5);
    light[0]->setColor(0.8, 0.8, 0.8, 0.1);
    light[0]->setAmbientLight();
    light[0]->setDiffuseLight();
    light[0]->enable();

    //light[1]是位置性光源（点光源），环境光可以考虑使用位置性光源
    light[1] = new Light(GL_LIGHT1);
    light[1]->setPosition(-10, 10, 0, 1);
    light[1]->setColor(1, 1, 1, 1);
    light[1]->setDiffuseLight();
    light[1]->enable();

    //light[2]是位置性光源（点光源，聚光灯） 还有一些问题。
    light[2] = new Light(GL_LIGHT2);
	light[2]->setPosition(eye[0], eye[1], eye[2], 1);//根据人的位置设置聚光灯的位置
    light[2]->setColor(1, 1, 1, 1);
    light[2]->setDiffuseLight();
    light[2]->setAgglomeration(100);
    light[2]->setSpotangle(45);
    light[2]->setLightDir(center[0], center[1], center[2]);//根据人的朝向设置聚光灯的朝向
    light[2]->setLimitRange();
    light[2]->enable();

	//light[3]是镜面光
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

	//地板
	flo = new Floor();
	flo->setMainTexture(io_texture);
	flo->setEntryTexture(io_texture);

	entryWall1 = new Wall(1, 20, -20, 0, 55);
	entryWall2 = new Wall(1, 20, 0, 0, 55);
	entryWall1->setTexture(wall_texture);
	entryWall2->setTexture(wall_texture);

	//房子的外围墙
	westWall = new Wall(1, 90, -49.5, 0, 0);
	northWall = new Wall(98, 1, 0, 0, -44.5);
	eastWall = new Wall(1, 90, 49.5, 0, 0);
	southWall = new Wall(50, 1, 24.5, 0, 44.5);
	westWall->setTexture(wall_texture);
	eastWall->setTexture(wall_texture);
	northWall->setTexture(wall_texture);
	southWall->setTexture(wall_texture);

	//各个房间的墙
	roomWall1 = new Wall(29, 1, -34.5, 0, 44.5);
	roomWall2 = new Wall(29, 1, -34.5, 0, 15);
	roomWall3 = new Wall(29, 1, -34.5, 0, -15);
	roomWall4 = new Wall(1, 30, 10, 0, -30);

	roomWall1->setTexture(wall_texture);
	roomWall2->setTexture(wall_texture);
	roomWall3->setTexture(wall_texture);
	roomWall4->setTexture(wall_texture);


	//带门的墙
	doorWall1 = new WallwithDoor(30.5, 1, 10, 15, -20, 0, 30, 90);
	doorWall2 = new WallwithDoor(30.5, 1, 10, 15, -20, 0, 0, 90);
	doorWall3 = new WallwithDoor(30.5, 1, 10, 15, -4.75, 0, -15);
	entrance = new WallwithDoor(20, 1, 10, 15, -10, 0, 65);
	doorWall1->setTexture(wall_texture);
	doorWall2->setTexture(wall_texture);
	doorWall3->setTexture(wall_texture);
	entrance->setTexture(wall_texture);


	//各种家具

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

	//床,长宽高={21.03,16.15,7.82} 缩小之后
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

	//钥匙长宽高 937mm 100mm 466mm 未换算
	keyObj_text = new GLTexture;
	keyObj_text->Load("data/13.bmp");

	keyObj = new ImportObj("data/key.obj");
	keyObj->setTexture(keyObj_text);
	keyObj->setScalef(0.05, 0.05, 0.05);
	keyObj->setPosition(-44, 4, -35);

	//旋转门
	doorTexture = new GLTexture;
	doorTexture->Load("Data/wood2.bmp");
	rotateDoor1 = new RotateDoor("Data/door1.obj",doorTexture, 13.5, 13, 1, -20, 0, 30, 90);
	rotateDoor2 = new RotateDoor("Data/door1.obj",doorTexture, 13.5, 13, 1, -20, 0, 0, 90);
	rotateDoor3 = new RotateDoor("Data/door1.obj",doorTexture, 13.5, 13, 1, -4.5, 0, -15,0);

	//逃脱门
	rotateDoor4 = new RotateDoor("Data/door1.obj", doorTexture, 13.5, 13, 1, -10, 0, 65, 0);

	//各种几何体
	sphere = new Sphere(1, 150, 150, 25, 6.5, -15);			//球体
	sphere->setTexture(wall_texture);
	// 棱柱(棱台)
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

	//电风扇
	fan = new ElectricFan(2, 1, 30, 18, -15);
	fan->open();

	//窗户
	window = new ImportObj("data/window2.obj");
	window->setScalef(0.01, 0.01, 0.01);
	window->setTexture(flower_text);
	window->setRotatef(-90, 0, 1, 0);
	window->setPosition(47, 2.5, 25);

	//沙发
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

	tableList = HouseList();			//房间显示列表

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


