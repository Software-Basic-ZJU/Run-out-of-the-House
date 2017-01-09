#include "Object\ImportObj.h"
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

GLfloat MAP_SIZE = 1000;      //地图的大小
VECTOR3 eyePosition ={0.0f, 4.0, 0.0f};   //视点坐标
VECTOR3 viewAtPosition ={0.0f, 4.0,-1.0};  // 参考点的坐标
bool bfullscreen = true;     // 全屏标识
GLfloat speed = 1.0f;       //移动速度
GLfloat theta = 0.0f;       //旋转的角度
GLfloat viewUp = 0.0f;      //向上和向下看的程度
GLTexture* user_text;
ImportObj* io;
int SCREEN_WIDTH=800,SCREEN_HEIGHT=600;

void SetViewByMouse()
{
	POINT mousePos;              //鼠标位置
	POINT middlePos;             //屏幕中心位置
	middlePos.x =SCREEN_WIDTH/2; // SCREEN_WIDHT 为屏幕宽度，全局变量，可改。
	middlePos.y =SCREEN_HEIGHT/2; 
   
	GetCursorPos(&mousePos);      //得到鼠标当前位置

	if(mousePos.x==middlePos.x&&mousePos.y==middlePos.y)    //如果鼠标没有动，返回。
		return ;
	SetCursorPos(middlePos.x, middlePos.y);                 //如果鼠标动了，则恢复到屏幕中心
       theta += GLfloat(-middlePos.x +mousePos.x)/500;      //旋转改变量
       viewUp +=GLfloat( middlePos.y - mousePos.y)/500;     //上下改变量
}

void reshape(int w,int h)
{

	if (h==0)										// 防止除零
	{
		h=1;									 
	}

	glViewport(0,0,w,h);						// 设置视口

	glMatrixMode(GL_PROJECTION);						// 设当前变换为投影变换
	glLoadIdentity();									// 当前矩阵初始为单位阵

	// 设置透视投影取景器
	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,1000.0f); 

	glMatrixMode(GL_MODELVIEW);							//  设当前变换为模型变换
	glLoadIdentity();			

}

GLvoid SetCamera(){

	SetViewByMouse();        //通过鼠标进行旋转变换
	if(theta>360) theta=0.0f; //显然角度不能大于度
	

	if (KEY_DOWN(VK_LEFT)||KEY_DOWN('A')) {     // 向左走
		eyePosition.x+=(viewAtPosition.z-eyePosition.z)*speed;
		//eyePosition.z+= -(viewAtPosition.x-eyePosition.x)*speed; 
	}

	if (KEY_DOWN(VK_RIGHT)||KEY_DOWN('D')){    //向右走
		eyePosition.x-=(viewAtPosition.z-eyePosition.z)*speed;
		//eyePosition.z-= -(viewAtPosition.x-eyePosition.x)*speed;	 
	}
	if (KEY_DOWN(VK_PRIOR)) viewUp +=0.02f;  //抬头看
	if (KEY_DOWN(VK_NEXT)) viewUp -=0.02f;   //低头看
	if (viewUp> 0.5f)	viewUp  = 0.5f;         //不要抬得太高
	if (viewUp<-0.6f)	viewUp =-0.6f;          

	if (KEY_DOWN(VK_UP)||KEY_DOWN('W'))        //前进
	{
		eyePosition.x+= (viewAtPosition.x-eyePosition.x)*speed;
		eyePosition.z+= (viewAtPosition.z-eyePosition.z)*speed;
	}

	if(KEY_DOWN(VK_DOWN)||KEY_DOWN('S'))     //后退
	{ 
		eyePosition.x-=(viewAtPosition.x-eyePosition.x)*speed;
		eyePosition.z-=(viewAtPosition.z-eyePosition.z)*speed;
	}

	if (eyePosition.x<-(MAP_SIZE-10))       //边界控制
		eyePosition.x= -(MAP_SIZE-10);
	if (eyePosition.x> (MAP_SIZE-10))
		eyePosition.x=  (MAP_SIZE-10);
	if (eyePosition.z<-(MAP_SIZE-10))
		eyePosition.z= -(MAP_SIZE-10);
	if (eyePosition.z> (MAP_SIZE-10))
		eyePosition.z=  (MAP_SIZE-10);

	viewAtPosition.x = float(eyePosition.x + cos(theta));      
	viewAtPosition.z = float(eyePosition.z + sin(theta));
	viewAtPosition.y = eyePosition.y;

	gluLookAt( eyePosition.x,eyePosition.y ,eyePosition.z,                     // 视点位置
		viewAtPosition.x, viewAtPosition.y+viewUp , viewAtPosition.z , //参考点位置
		0.0,1.0,0.0);  
	glutPostRedisplay();
	
}


void render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	
	SetCamera();

	io->draw();
	
	glLoadIdentity();
	glFlush();
	glutSwapBuffers();
}

void init()
{

	glShadeModel(GL_SMOOTH);						 
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			 
	glClearDepth(1.0f);							 
	glEnable(GL_DEPTH_TEST);						 
	glDepthFunc(GL_LEQUAL);							 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
	// 加入光照
	GLfloat light0Pos[4] = {1.0,1.0,1.0,0.0};
	GLfloat light1Pos[4] = {-1.0f,1.0f,-1.0f,0.0f};

	GLfloat lightAmbient[4] ={0.0,0.5,1.0,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,light0Pos);
	glLightfv(GL_LIGHT1,GL_POSITION,light1Pos);
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightAmbient);
	glLightfv(GL_LIGHT1,GL_AMBIENT,lightAmbient);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	user_text=new GLTexture;
	user_text->Load("data/no1.bmp");
	user_text->Use();
	
	io=new ImportObj("data/door2.obj");
	io->setTexture(user_text);
	io->setScalef(0.1);
}

void idle()
{
	glutPostRedisplay();
}
void keyboard( unsigned char key, int x, int y )
{
	switch( key ) 
	{
	case 'f' : case 'F' :
		if (bfullscreen)
		{
			SCREEN_WIDTH =800;
			SCREEN_HEIGHT=600;
			glutReshapeWindow(SCREEN_WIDTH , SCREEN_HEIGHT);
			glutPositionWindow(100,100);
		}
		else
		{
			SCREEN_WIDTH =1280;
			SCREEN_HEIGHT=1024;
			glutFullScreen();
		}
		bfullscreen = !bfullscreen;
		break;
	case 'q' : 
	case 'Q' :
		exit( 0 );
		break;
	case 'r' : case 'R' :
		glutPostRedisplay();
		break;

	}
}

int main()
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("3D Tech- GLUT Tutorial");

	init();

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc( keyboard );

	glutMainLoop();
}
