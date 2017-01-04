#pragma once
#include "Geometry.h"

class Cylinder:public Geometry{
private:
	GLfloat radius, height;			//底面圆半径、圆柱高
	GLint slice;					//横向分片数
	void drawCylinder();			//绘制单位圆柱
public:
	Cylinder(GLfloat radius = 1, GLfloat height = 1,GLint slice = 100,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);	
	virtual void render();
};