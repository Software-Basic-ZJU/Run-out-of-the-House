#include "..\Geometry\Cubic.h"
#include <list>

class Floor{
private:
	GLfloat length, width;				//�ذ峤����
	list<Geometry *> geoList;			//���õ��ļ������б�
public:
	Floor(GLfloat length = 100, GLfloat width = 100);

	void render();
};