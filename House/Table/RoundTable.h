#pragma once
#pragma execution_character_set("utf-8")
#include "../../Geometry/Cylinder.h"
#include <list>

// Բ��
class RoundTable{
private:
	GLfloat angle;				//��Y����ת�Ƕ�
	list<Geometry *> geoList;	//�漰���ļ������б�
public:
	GLfloat radius;				//Բ����뾶
	GLfloat height;				//Բ���ĸ߶�
	GLfloat x, y, z;

	RoundTable(GLfloat radius, GLfloat height,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0);

	void rotateY(GLfloat angle);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void render();
};