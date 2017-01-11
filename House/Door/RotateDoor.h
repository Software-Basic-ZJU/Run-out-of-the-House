#pragma once
#pragma execution_character_set("utf-8")
#include "Door.h"
#include "../../Model/ImportObj.h"

//��ת��
class RotateDoor :public Door{
private:
	GLfloat speed;					//��ת�ٶ�
	GLfloat fRotate;				//��һ�ߵ���ת�Ƕ�
	ImportObj *door;				//�����objģ��
	bool direction;					//��ת����: true��ʱ��;false˳ʱ��
	bool status;					//�ŵ�״̬: trueΪ��;falseΪ�ر�
public:

	RotateDoor(char *filename, GLTexture *texture, 
		GLfloat width, GLfloat height, GLfloat thickness,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0,
		GLfloat speed = 1.0, bool direction = false, bool status = false);
	
	bool getStatus();			//��ȡ�ŵĿ���״̬

	void openDoor();			//����
		
	void closeDoor();			//����

	virtual void render();		
};