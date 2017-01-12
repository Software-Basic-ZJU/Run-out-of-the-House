#pragma once
#pragma execution_character_set("utf-8")
#include "../../Model/ImportObj.h"

class ElectricFan{
private:
	ImportObj *fan;			//Objָ��
	GLTexture *texture;		//����
	GLfloat radius;			//���Ȱ뾶
	GLfloat height;			//���ȵĸ߶ȳߴ�
	GLfloat x, y, z;		//λ������
	GLfloat fRotate;		//��ת�����ĽǶ�
	GLfloat speed;			//������ת�ٶ�
	bool status;			//����״̬:falseΪ�ر�,trueΪ��
public:
	ElectricFan(GLfloat radius, GLfloat height,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat speed = 10.0);

	void open();

	void close();

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void render();
};