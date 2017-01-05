#pragma once
#include "..\Geometry\Cubic.h"

// �ذ�
class Floor{
private:
	GLfloat length, width;				//�ذ峤����
	Geometry *mainFloor, *entrance;					//���õļ�����ָ��
public:
	Floor(GLfloat length = 100, GLfloat width = 90);

	void render();
};