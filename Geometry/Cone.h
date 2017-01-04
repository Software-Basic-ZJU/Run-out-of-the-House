#include "Geometry.h"

class Cone:public Geometry{
private:
	GLfloat radius, height;			//�뾶���߶�
	GLint slice;					//�����Ƭ
	void drawCone();				//���Ƶ�λԲ׶
public:
	Cone(GLfloat radius = 1, GLfloat height = 1, GLint slice = 100,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	virtual void render();
};