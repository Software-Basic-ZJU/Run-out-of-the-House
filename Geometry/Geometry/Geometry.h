#pragma once
#include <iostream>
#include <math.h>
#include <gl/glut.h>
#define PI 3.141593

//������
class Geometry{
public:		
	bool hidden;							//�Ƿ�����
	GLfloat x, y, z;						//��ά����
	GLfloat angle;							//��ת�Ƕ�
	GLfloat rotX, rotY, rotZ;				//��ת���Ƶ�����

	Geometry(GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);	//�����幹��
	
	void rotateX(GLfloat angle);							//��x�᷽������ת
	void rotateY(GLfloat angle);							//��y�᷽������ת
	void rotateZ(GLfloat angle);							//��z�᷽������ת
	void rotate(GLfloat angle,GLfloat x, GLfloat y, GLfloat z);			//���Զ���������ת
	void setPosition(GLfloat x, GLfloat y, GLfloat z);		//����λ��

	void setTexture();										//��������
	void isHide(bool hidden);								//�Ƿ�����
};


//������Ҫ���¶���draw��render����