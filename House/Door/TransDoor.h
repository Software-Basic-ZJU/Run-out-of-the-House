#pragma once
#pragma execution_character_set("utf-8")
#include "Door.h"

//ƽ����
class TransDoor :public Door{
private:
	GLfloat speed;					//ƽ���ٶ�
	GLfloat disappear;				//����ʧ�İٷֱ�
	bool direction;					//���ƶ��ķ���: falseΪ�����ң�trueΪ���ҵ���(�������)
	bool status;					//�ſ���״̬: falseΪ�ر�;trueΪ��
public:
	TransDoor(GLfloat width, GLfloat height, GLfloat thickness,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0,
		GLfloat speed = 0.001, bool direction = false, bool status = false);

	bool getStatus();			//��ȡ�ŵĿ���״̬

	void openDoor();			//����

	void closeDoor();			//����

	virtual void render();

};