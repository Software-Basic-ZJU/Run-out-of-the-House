#pragma once
#pragma execution_character_set("utf-8")
#include "Door.h"

//平移门
class TransDoor :public Door{
private:
	GLfloat speed;					//平移速度
	GLfloat disappear;				//门消失的百分比
	bool direction;					//门移动的方向: false为从左到右，true为从右到左(相对意义)
	bool status;					//门开闭状态: false为关闭;true为打开
public:
	TransDoor(GLfloat width, GLfloat height, GLfloat thickness,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0,
		GLfloat speed = 0.01, bool direction = false, bool status = false);

	bool getStatus();			//获取门的开闭状态

	void openDoor();			//开门

	void closeDoor();			//关门

	virtual void render();

};