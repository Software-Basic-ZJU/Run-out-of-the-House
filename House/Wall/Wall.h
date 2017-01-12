#pragma once
#pragma execution_character_set("utf-8")
#include "..\..\Geometry\Cubic.h"

//ǽ�棨������)
class Wall{
private:
	GLfloat height = 30;		//�߹̶�Ϊ30
	Geometry *cubic;				//���õ��ļ�����ָ��
public:
	GLfloat lenth, width;		//����
	GLfloat x, y, z;			//����

	//�ش�����Ϊ���Ϳ��߶����ն�
	Wall(GLfloat length, GLfloat width,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void setTexture(GLTexture *texture);			//��������

	void render();
};