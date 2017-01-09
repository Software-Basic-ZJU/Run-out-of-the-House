//
//  main.cpp
//  teapot
//
//  Created by crcrcry on 2016/11/7.
//  Copyright © 2016年 crcrcry. All rights reserved.
//

// This assignment may cost you some efferts, so I give you some important HINTS, hope that may help you.
// Enjoy the coding and thinking, do pay more attention to the library functions used in OPENGL, such as how they are used? what are the parameters used? and why?

// 实验报告里面多写点感想，即对函数的理解，以及调用的顺序，步骤等。思考为什么是这样子调用的，为什么参数是这样子设置的？。。。等等你觉得值得研究的问题。
#include <iostream>
#include <stdlib.h>
#include <GLUT/GLUT.h>  //mac glut

bool bPersp = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

void updateView(int width, int height)
{
    glViewport(0,0,width,height);				// Reset The Current Viewport
    
    glMatrixMode(GL_PROJECTION);			// Select The Projection Matrix
    glLoadIdentity();							// Reset The Projection Matrix
    
    float whRatio = (GLfloat)width/(GLfloat)height;
    
    if (bPersp){
        gluPerspective(120, whRatio, 0.5, 20);
    }
    else
        glOrtho(-3 ,3, -3, 3,-100,100);
    
    glMatrixMode(GL_MODELVIEW);					// Select The Modelview Matrix
}

void reshape(int width, int height)
{
    if (height==0)								// Prevent A Divide By Zero By
    {
        height=1;								// Making Height Equal One
    }
    
    wHeight = height;
    wWidth = width;
    
    updateView(wHeight, wWidth);
}

void idle()
{
    glutPostRedisplay();
}

float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};

void key(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        case 'q': {exit(0); break; }
        case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth);break; }
            
        case 'o': {bWire = !bWire; break;}
            
        case 'a': {
            eye[0] -= 0.5;
            break;
        }
        case 'd': {
            eye[0] += 0.5;
            break;
        }
        case 'w': {
            eye[1] += 0.5;
            break;
        }
        case 's': {
            eye[1] -= 0.5;
            break;
        }
        case 'z': {
            eye[2] += 0.5;
            break;
        }
        case 'c': {
            eye[2] -= 0.5;
            break;
        }
    }
}

//l、w、h：床面的长宽高
void bed(float l, float w, float h){
    /*床头*/
    glPushMatrix();
    glTranslatef(0.4*l, h+0.4, 0);
    glScalef(l*0.2, 0.3, w);
    glutSolidCube(1.0);
    glPopMatrix();
    
    /*床面*/
    glPushMatrix();
    glTranslatef(0, h, 0);
    glScalef(l, 0.5, w);
    glutSolidCube(1.0);
    glPopMatrix();
    
    /*枕头：圆柱比较好，先用立方体代替*/
    glPushMatrix();
    glTranslatef(0.2*l, h+0.25, 0);
    //枕头1
    glPushMatrix();
    glTranslated(0, 0, 0.25*w);
    glScalef(0.15*l, 0.4, 0.4*w);
    glutSolidCube(1);
    glPopMatrix();
    //枕头2
    glPushMatrix();
    glTranslated(0, 0, -0.25*w);
    glScalef(0.15*l, 0.4, 0.4*w);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
}

//l、w、h：桌面的长、宽、离地面的高度
void table_formal(float l, float w, float h){
    /*桌面*/
    glPushMatrix();
    glTranslatef(0, h, 0);
    glScalef(l, 0.5, w);
    glutSolidCube(1.0);
    glPopMatrix();
    
    /*桌腿*/
    glPushMatrix();
    glTranslatef(0.3*l, 0, 0.3*w);
    glScalef(0.5, 2*(h-0.25), 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.3*l, 0, 0.3*w);
    glScalef(0.5, 2*(h-0.25), 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.3*l, 0, -0.3*w);
    glScalef(0.5, 2*(h-0.25), 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.3*l, 0, -0.3*w);
    glScalef(0.5, 2*(h-0.25), 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
}

//电风扇
//open：true为打开状态，false为关闭状态
//速度[5,20]比较合适
void fan(bool open, float speed){
    static float fRotate = 0;
    
    glRotated(fRotate, 0, 0, 1);
    
    glutSolidSphere(0.5, 40, 50);
    
    glPushMatrix();
    glTranslated(1.2, 0, 0);
    glScaled(1.6, 0.4, 0.4);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(-1.2, 0, 0);
    glScaled(1.6, 0.4, 0.4);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, 1.2, 0);
    glScaled(0.4, 1.6, 0.4);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, -1.2, 0);
    glScaled(0.4, 1.6, 0.4);
    glutSolidCube(1);
    glPopMatrix();
    
    if(open)    fRotate += speed;
}

//旋转门
//h w d：门的高宽厚
//direction：true:上方逆时针 false:上方顺时针
//speed:[0, 2]差不多够用
//run:是否正在运动
void door_formal(float h, float w, float d, float speed, bool direction, bool run){
    int k = 1;
    int dir = (direction) ? 1 : -1;
    static float fRotate = 0.0f;

    glPushMatrix();
    glScalef(h, w, d);
    
    glTranslated(0.5*w*(-dir), 0, 0);
    glRotated(fRotate*dir, 0, 1, 0);
    glTranslated(0.5*w*dir, -0.55, 0);
    
    glutSolidCube(k);
    glPopMatrix();
    if (run && fRotate <= 90) fRotate += speed;
}

//平移门
//h w d：门的高宽厚
//运动方向：true:left false:right
//speed:[0.004, 0.008]差不多够用
//open：true：门正在打开 false：门没有正在打开
//close：true：门正在关上 false：门没有正在关上
//open和close同时为true或同时为false，门保持当前状态不变
void door_special(float h, float w, float d, float speed, bool direction, bool open, bool close){
    int k = 1;  //立方体大小系数
    int dir = (direction) ? -1 : 1;
    static float disappear = 0; //门消失的百分比，门打开时100%消失，门关闭时0%消失，初始门是关闭的

    glPushMatrix();
    glScalef(h, w, d);
    
    glTranslated(disappear*0.5*k*dir, 0.55, 0);
    glScaled((1-disappear), 1, 1);
    
    //printf("%f\n", disappear);
    
    glutSolidCube(k);
    glPopMatrix();
    if(open && disappear < 1) disappear += speed;
    if(close && disappear > 0) disappear -= speed;
}

void redraw()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();					// Reset The Current Modelview Matrix
    
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              0, 1, 0);			// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上
    
    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_pos[] = {5,5,5,1};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glEnable(GL_LIGHT0);

    //fan(true, 9);
    
    //door_formal(1.2, 2, 0.2, 1, false, true);
    
    //door_special(1.4, 2, 1, 0.008, true, true, false);

    //table_formal(3, 2, 1);
    
    //bed(3,2,0.2);
    
    glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(480,480);
    int windowHandle = glutCreateWindow("API test");
    
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}


