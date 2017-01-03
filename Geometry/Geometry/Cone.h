#include "Geometry.h"

class Cone:public Geometry{
private:
	GLfloat radius, height;			//半径，高度
	GLint slice;					//横向分片
	void drawCone();				//绘制单位圆锥
public:
	Cone(GLfloat radius = 1, GLfloat height = 1, GLint slice = 50,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void render();
};