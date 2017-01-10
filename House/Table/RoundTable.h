#pragma once
#pragma execution_character_set("utf-8")
#include "../../Geometry/Cylinder.h"
#include <list>

// 圆桌
class RoundTable{
private:
	GLfloat angle;				//绕Y轴旋转角度
	list<Geometry *> geoList;	//涉及到的几何体列表
public:
	GLfloat radius;				//圆桌面半径
	GLfloat height;				//圆桌的高度
	GLfloat x, y, z;

	RoundTable(GLfloat radius, GLfloat height,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0);

	void rotateY(GLfloat angle);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void render();
};