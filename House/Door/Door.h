#pragma once
#pragma execution_character_set("utf-8")
#include "../../Geometry/Cubic.h"

class Door{
protected:
	GLfloat width, thickness, height;			//�ŵĿ�ȡ������߶�
	GLfloat x, y, z;							//����λ��
	GLfloat speed;								//��ת�ٶ�
	Cubic *door;								//�ŵļ�����
	GLfloat fRotate = 0;						//��������ת�Ƕ�
	GLfloat angle;							//��������Y�����ת�Ƕ�
	bool direction;								//true: ��ʱ��; false: ˳ʱ��
	bool run;									//�Ƿ����˶�
public:
	Door(GLfloat width, GLfloat height, GLfloat thickness,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void rotateY(GLfloat angle);

	virtual void render();
};