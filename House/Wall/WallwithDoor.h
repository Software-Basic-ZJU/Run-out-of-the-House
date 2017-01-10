#pragma once
#pragma execution_character_set("utf-8")
#include "..\..\Geometry\Cubic.h"

//墙壁（带有门在正中间）
class WallwithDoor{
private:
	GLfloat height = 20;		//墙高度钦定为20
	GLfloat angle;				//绕Y轴旋转角度
	Geometry *ltCubic, *rtCubic, *topCubic;		//左侧、右侧、上方立方体
public:
	GLfloat length, width;		//墙的长宽
	GLfloat doorWidth, doorHei;	//门的宽度（沿着墙的长度方向）和高（宽默认与墙一致）
	GLfloat x, y, z;

	// 必传参数：墙的长宽，门的长
	WallwithDoor(GLfloat length, GLfloat width, GLfloat doorWidth, GLfloat doorHei = 15,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void setTexture(GLTexture *texture);			//设置纹理

	void rotateY(GLfloat angle);

	void render();
};