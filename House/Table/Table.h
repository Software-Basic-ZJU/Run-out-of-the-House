#pragma once
#pragma execution_character_set("utf-8")
#include "..\..\Geometry\Cubic.h"
#include <list>

// 方桌
class Table{
private:
	GLfloat length, width, height;		//长宽高
	GLfloat x, y, z;					//坐标
	GLfloat angle;						//绕Y轴旋转角度
	list<Geometry *> geoList;			//涉及到的几何体列表
public:
	Table(GLfloat length, GLfloat width, GLfloat height,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0);

	void rotateY(GLfloat angle);

	void setTexture(GLTexture *texture);			//设置纹理

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void render();
};