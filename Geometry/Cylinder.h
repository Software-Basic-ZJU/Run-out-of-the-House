#include "Geometry.h"

class Cylinder:public Geometry{
private:
	GLfloat radius, height;			//����Բ�뾶��Բ����
	GLint slice;					//�����Ƭ��
	void drawCylinder();			//���Ƶ�λԲ��
public:
	Cylinder(GLfloat radius = 1, GLfloat height = 1,GLint slice = 50,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);	
	void render();
};