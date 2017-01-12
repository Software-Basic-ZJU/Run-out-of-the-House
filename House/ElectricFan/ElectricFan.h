#pragma once
#pragma execution_character_set("utf-8")
#include "../../Model/ImportObj.h"

class ElectricFan{
private:
	ImportObj *fan;			//Obj指针
	GLTexture *texture;		//纹理
	GLfloat radius;			//风扇半径
	GLfloat height;			//风扇的高度尺寸
	GLfloat x, y, z;		//位置坐标
	GLfloat fRotate;		//自转动画的角度
	GLfloat speed;			//风扇旋转速度
	bool status;			//开关状态:false为关闭,true为打开
public:
	ElectricFan(GLfloat radius, GLfloat height,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat speed = 10.0);

	void open();

	void close();

	void setPosition(GLfloat x, GLfloat y, GLfloat z);

	void render();
};