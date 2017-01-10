#pragma once
#pragma execution_character_set("utf-8")
#include "..\Geometry\Cubic.h"
#include <list>

// 床
class Bed{
private:
	GLfloat angle;								//绕y轴的旋转角度
	list<Geometry *> geoList;					//相关几何体的链表
public:
	GLfloat length, width, height;				//床的长宽高
	GLfloat x, y, z;							//坐标

	Bed(GLfloat length, GLfloat width, GLfloat height,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0);

	void rotateY(GLfloat angle);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void render();
};