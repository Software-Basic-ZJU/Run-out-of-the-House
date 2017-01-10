#pragma once
#pragma execution_character_set("utf-8")
#include "..\Geometry\Cubic.h"
#include <list>

// ��
class Bed{
private:
	GLfloat angle;								//��y�����ת�Ƕ�
	list<Geometry *> geoList;					//��ؼ����������
public:
	GLfloat length, width, height;				//���ĳ����
	GLfloat x, y, z;							//����

	Bed(GLfloat length, GLfloat width, GLfloat height,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0);

	void rotateY(GLfloat angle);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void render();
};