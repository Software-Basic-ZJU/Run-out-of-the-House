#include "Object\ImportObj.h"
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

GLfloat MAP_SIZE = 1000;      //��ͼ�Ĵ�С
VECTOR3 eyePosition ={0.0f, 4.0, 0.0f};   //�ӵ�����
VECTOR3 viewAtPosition ={0.0f, 4.0,-1.0};  // �ο��������
bool bfullscreen = true;     // ȫ����ʶ
GLfloat speed = 1.0f;       //�ƶ��ٶ�
GLfloat theta = 0.0f;       //��ת�ĽǶ�
GLfloat viewUp = 0.0f;      //���Ϻ����¿��ĳ̶�
GLTexture* user_text;
ImportObj* io;
int SCREEN_WIDTH=800,SCREEN_HEIGHT=600;

void SetViewByMouse()
{
	POINT mousePos;              //���λ��
	POINT middlePos;             //��Ļ����λ��
	middlePos.x =SCREEN_WIDTH/2; // SCREEN_WIDHT Ϊ��Ļ��ȣ�ȫ�ֱ������ɸġ�
	middlePos.y =SCREEN_HEIGHT/2; 
   
	GetCursorPos(&mousePos);      //�õ���굱ǰλ��

	if(mousePos.x==middlePos.x&&mousePos.y==middlePos.y)    //������û�ж������ء�
		return ;
	SetCursorPos(middlePos.x, middlePos.y);                 //�����궯�ˣ���ָ�����Ļ����
       theta += GLfloat(-middlePos.x +mousePos.x)/500;      //��ת�ı���
       viewUp +=GLfloat( middlePos.y - mousePos.y)/500;     //���¸ı���
}

void reshape(int w,int h)
{

	if (h==0)										// ��ֹ����
	{
		h=1;									 
	}

	glViewport(0,0,w,h);						// �����ӿ�

	glMatrixMode(GL_PROJECTION);						// �赱ǰ�任ΪͶӰ�任
	glLoadIdentity();									// ��ǰ�����ʼΪ��λ��

	// ����͸��ͶӰȡ����
	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,1000.0f); 

	glMatrixMode(GL_MODELVIEW);							//  �赱ǰ�任Ϊģ�ͱ任
	glLoadIdentity();			

}

GLvoid SetCamera(){

	SetViewByMouse();        //ͨ����������ת�任
	if(theta>360) theta=0.0f; //��Ȼ�ǶȲ��ܴ��ڶ�
	

	if (KEY_DOWN(VK_LEFT)||KEY_DOWN('A')) {     // ������
		eyePosition.x+=(viewAtPosition.z-eyePosition.z)*speed;
		//eyePosition.z+= -(viewAtPosition.x-eyePosition.x)*speed; 
	}

	if (KEY_DOWN(VK_RIGHT)||KEY_DOWN('D')){    //������
		eyePosition.x-=(viewAtPosition.z-eyePosition.z)*speed;
		//eyePosition.z-= -(viewAtPosition.x-eyePosition.x)*speed;	 
	}
	if (KEY_DOWN(VK_PRIOR)) viewUp +=0.02f;  //̧ͷ��
	if (KEY_DOWN(VK_NEXT)) viewUp -=0.02f;   //��ͷ��
	if (viewUp> 0.5f)	viewUp  = 0.5f;         //��Ҫ̧��̫��
	if (viewUp<-0.6f)	viewUp =-0.6f;          

	if (KEY_DOWN(VK_UP)||KEY_DOWN('W'))        //ǰ��
	{
		eyePosition.x+= (viewAtPosition.x-eyePosition.x)*speed;
		eyePosition.z+= (viewAtPosition.z-eyePosition.z)*speed;
	}

	if(KEY_DOWN(VK_DOWN)||KEY_DOWN('S'))     //����
	{ 
		eyePosition.x-=(viewAtPosition.x-eyePosition.x)*speed;
		eyePosition.z-=(viewAtPosition.z-eyePosition.z)*speed;
	}

	if (eyePosition.x<-(MAP_SIZE-10))       //�߽����
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

	gluLookAt( eyePosition.x,eyePosition.y ,eyePosition.z,                     // �ӵ�λ��
		viewAtPosition.x, viewAtPosition.y+viewUp , viewAtPosition.z , //�ο���λ��
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
	// �������
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
