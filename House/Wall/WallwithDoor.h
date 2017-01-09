#pragma once
#pragma execution_character_set("utf-8")
#include "..\..\Geometry\Cubic.h"

//ǽ�ڣ������������м䣩
class WallwithDoor{
private:
	GLfloat length, width;		//ǽ�ĳ���
	GLfloat doorWidth, doorHei;	//�ŵĿ�ȣ�����ǽ�ĳ��ȷ��򣩺͸ߣ���Ĭ����ǽһ�£�
	GLfloat height = 20;		//ǽ�߶��ն�Ϊ20
	GLfloat x, y, z;
	GLfloat angle;				//��Y����ת�Ƕ�
	Geometry *ltCubic, *rtCubic, *topCubic;		//��ࡢ�Ҳࡢ�Ϸ�������
public:
	// �ش�������ǽ�ĳ����ŵĳ�
	WallwithDoor(GLfloat length, GLfloat width, GLfloat doorWidth, GLfloat doorHei = 15,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void rotateY(GLfloat angle);

	void render();
};