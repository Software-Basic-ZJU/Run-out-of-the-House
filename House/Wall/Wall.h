#pragma once
#pragma execution_character_set("utf-8")
#include "..\..\Geometry\Cubic.h"

//墙面（不带门)
class Wall{
private:
	GLfloat lenth, width;		//长宽
	GLfloat height = 20;		//高固定为20
	GLfloat x, y, z;			//坐标
	Geometry *cubic;				//所用到的几何体指针
public:
	//必传参数为长和宽，高度已钦定
	Wall(GLfloat length, GLfloat width,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void setTexture(GLTexture *texture);			//设置纹理

	void render();
};