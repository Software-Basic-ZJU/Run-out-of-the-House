#pragma once
#include <iostream>
#include <math.h>
#include <gl/glut.h>
#define PI 3.141593
using namespace std;

//几何体
class Geometry{
public:		
	bool hidden;							//是否隐藏
	GLfloat x, y, z;						//三维坐标
	GLfloat angle;							//旋转角度
	GLfloat rotX = 0, rotY = 0, rotZ = 0;				//旋转所绕的向量

	Geometry(GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);	//几何体构造

	void setColor(GLfloat red, GLfloat green, GLfloat blue);//设置RGB颜色
	
	void rotateX(GLfloat angle);							//绕x轴方向自旋转
	void rotateY(GLfloat angle);							//绕y轴方向自旋转
	void rotateZ(GLfloat angle);							//绕z轴方向自旋转
	void rotate(GLfloat angle,GLfloat x, GLfloat y, GLfloat z);			//绕自定义向量旋转
	void setPosition(GLfloat x, GLfloat y, GLfloat z);		//设置位置

	void setTexture();										//设置纹理
	void isHide(bool hidden);								//是否隐藏

	virtual void render()=0;
};


//子类需要重新定义draw和render函数