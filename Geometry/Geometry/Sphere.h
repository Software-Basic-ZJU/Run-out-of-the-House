#include "Geometry.h"

class Sphere:public Geometry{
private:
	void drawSphere();		//绘制单位球体
	GLfloat radius;			//半径
	GLint M, N;				//横纵向分块数
public:

	// M,N表示球的横纵向被切分为几块
	Sphere(GLfloat radius = 1, GLint M = 50, GLint N = 50,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void setRadius(GLfloat radius);				//设置半径

	void setMspice(GLfloat M);					//设置横向切片数

	void setNspice(GLfloat N);					//设置纵向切片数

	void render();
};