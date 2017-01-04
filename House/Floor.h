#include "..\Geometry\Cubic.h"
#include <list>

class Floor{
private:
	GLfloat length, width;				//地板长、宽
	list<Geometry *> geoList;			//所用到的几何体列表
public:
	Floor(GLfloat length = 100, GLfloat width = 100);

	void render();
};