#pragma once
#include "..\Geometry\Cubic.h"

// 地板
class Floor{
private:
	GLfloat length, width;				//地板长、宽
	Geometry *mainFloor, *entrance;					//所用的几何体指针
public:
	Floor(GLfloat length = 100, GLfloat width = 90);

	void setMainTexture(GLTexture *texture);		//室内地板纹理
	void setEntryTexture(GLTexture *texture);		//玄关地板纹理

	void render();
};