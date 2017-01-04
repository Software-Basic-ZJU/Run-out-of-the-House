#include "Geometry.h"

class Cubic:public Geometry{
private:
	static GLfloat cubic[8][3];					//��λ�����������
	static GLint cubicIndex[6][4];				//���涥����������
	GLfloat length, width, height;				//�����

	void drawCubic();
public:
	Cubic(GLfloat length, GLfloat width, GLfloat height,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);		

	virtual void render();											//��Ⱦ����

};