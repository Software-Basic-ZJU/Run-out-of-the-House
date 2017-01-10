#pragma once
#pragma execution_character_set("utf-8")
#include "Door.h"

//��ת��
class RotateDoor :public Door{
private:
	GLfloat speed;					//��ת�ٶ�
	GLfloat fRotate;				//��һ�ߵ���ת�Ƕ�
	bool direction;					//��ת����: true��ʱ��;false˳ʱ��
	bool status;					//�ŵ�״̬: trueΪ��;falseΪ�ر�
public:

	RotateDoor(GLfloat width, GLfloat height, GLfloat thickness,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0,
		GLfloat speed = 0.1, bool direction = false, bool status = false);
	
	bool getStatus();			//��ȡ�ŵĿ���״̬

	void openDoor();			//����
		
	void closeDoor();			//����

	virtual void render();		
};