#pragma once
#include "Geometry.h"

class Cubic:public Geometry{
private:
	static GLfloat cubic[8][3];					//单位立方体坐标点
	static GLint cubicIndex[6][4];				//各面顶点坐标索引
	GLfloat length, width, height;				//长宽高

	void drawCubic();
public:
	Cubic(GLfloat length, GLfloat width, GLfloat height,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);		

	void resize(GLfloat length, GLfloat width, GLfloat height);		//重设尺寸

	virtual void render();											//渲染函数

};