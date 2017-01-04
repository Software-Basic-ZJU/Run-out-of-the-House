#pragma once
#pragma execution_character_set("utf-8")
#include "..\Geometry\Cubic.h"

//ǽ�ڣ������������м䣩
class WallwithDoor{
private:
	GLfloat length, width;		//ǽ�ĳ���
	GLfloat doorLen, doorHei;	//�ŵĳ�������ǽ�ĳ��ȷ��򣩺͸ߣ���Ĭ����ǽһ�£�
	GLfloat height = 20;		//ǽ�߶��ն�Ϊ20
	GLfloat x, y, z;
	Geometry *ltCubic, *rtCubic, *topCubic;		//��ࡢ�Ҳࡢ�Ϸ�������
public:
	// �ش�������ǽ�ĳ����ŵĳ�
	WallwithDoor(GLfloat length, GLfloat width, GLfloat doorLen, GLfloat doorHei = 15,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void render();
};