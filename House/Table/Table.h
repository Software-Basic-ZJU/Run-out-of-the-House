#pragma once
#pragma execution_character_set("utf-8")
#include "..\..\Geometry\Cubic.h"
#include <list>

// ����
class Table{
private:
	GLfloat length, width, height;		//�����
	GLfloat x, y, z;					//����
	GLfloat angle;						//��Y����ת�Ƕ�
	list<Geometry *> geoList;			//�漰���ļ������б�
public:
	Table(GLfloat length, GLfloat width, GLfloat height,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0);

	void rotateY(GLfloat angle);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void render();
};