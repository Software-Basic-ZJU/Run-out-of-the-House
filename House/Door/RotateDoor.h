#pragma once
#pragma execution_character_set("utf-8")
#include "Door.h"
#include "../../Model/ImportObj.h"

//旋转门
class RotateDoor :public Door{
private:
	GLfloat speed;					//旋转速度
	GLfloat fRotate;				//绕一边的旋转角度
	ImportObj *door;				//导入的obj模型
	bool direction;					//旋转方向: true逆时针;false顺时针
	bool status;					//门的状态: true为打开;false为关闭
public:

	RotateDoor(char *filename, GLTexture *texture, 
		GLfloat width, GLfloat height, GLfloat thickness,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0, GLfloat angle = 0,
		GLfloat speed = 1.0, bool direction = false, bool status = false);
	
	bool getStatus();			//获取门的开闭状态

	void openDoor();			//开门
		
	void closeDoor();			//关门

	virtual void render();		
};