#pragma once
#pragma execution_character_set("utf-8")
#include "../../Geometry/Cubic.h"

class Door{
protected:
	GLfloat width, thickness, height;			//门的宽度、厚度与高度
	GLfloat x, y, z;							//坐标位置
	GLfloat speed;								//旋转速度
	Cubic *door;								//门的几何体
	GLfloat fRotate = 0;						//开关门旋转角度
	GLfloat angle;							//门自身绕Y轴的自转角度
	bool direction;								//true: 逆时针; false: 顺时针
	bool run;									//是否在运动
public:
	Door(GLfloat width, GLfloat height, GLfloat thickness,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0);

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void rotateY(GLfloat angle);

	virtual void render();
};