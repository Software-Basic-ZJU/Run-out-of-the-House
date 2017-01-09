#pragma once
#pragma execution_character_set("utf-8")
#include "..\..\Geometry\Cubic.h"

//ǽ�棨������)
class Wall{
private:
	GLfloat lenth, width;		//����
	GLfloat height = 20;		//�߹̶�Ϊ20
	GLfloat x, y, z;			//����
	Geometry *cubic;				//���õ��ļ�����ָ��
public:
	//�ش�����Ϊ���Ϳ��߶����ն�
	Wall(GLfloat length, GLfloat width,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void render();
};