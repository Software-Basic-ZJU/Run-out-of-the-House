#include "Geometry.h"

class Sphere:public Geometry{
private:
	void drawSphere();		//���Ƶ�λ����
	GLfloat radius;			//�뾶
	GLint M, N;				//������ֿ���
public:

	// M,N��ʾ��ĺ������з�Ϊ����
	Sphere(GLfloat radius = 1, GLint M = 50, GLint N = 50,
		GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void setRadius(GLfloat radius);				//���ð뾶

	void setMspice(GLfloat M);					//���ú�����Ƭ��

	void setNspice(GLfloat N);					//����������Ƭ��

	void render();
};