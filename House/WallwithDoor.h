#pragma once
#pragma execution_character_set("utf-8")
#include "..\Geometry\Cubic.h"

//墙壁（带有门在正中间）
class WallwithDoor{
private:
	GLfloat length, width;		//墙的长宽
	GLfloat doorLen, doorHei;	//门的长（沿着墙的长度方向）和高（宽默认与墙一致）
	GLfloat height = 20;		//墙高度钦定为20
	GLfloat x, y, z;
	Geometry *ltCubic, *rtCubic, *topCubic;		//左侧、右侧、上方立方体
public:
	// 必传参数：墙的长宽，门的长
	WallwithDoor(GLfloat length, GLfloat width, GLfloat doorLen, GLfloat doorHei = 15,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void render();
};