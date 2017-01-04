#pragma once
#include "..\Geometry\Cubic.h"

// 地板
class Floor{
private:
	GLfloat length, width;				//地板长、宽
	Geometry *cubic;					//所用的几何体指针
public:
	Floor(GLfloat length = 100, GLfloat width = 90);

	void render();
};