#include "Geometry.h"

// 仅支持凸多边形的棱柱棱台
// 底面各顶点坐标，传入时须平行于xOz平面!!!!!!!!!!!!!!!!!!!!!!!!
class Prism :public Geometry{
private:

	GLfloat **btmVertexArr;							//底面多边形各定点二维数组，按顺序传入
	GLfloat **topVertexArr;							//顶部多边形各定点二维数组，按顺序传入

	int vertNum;									//多边形边数,最大支持20边
	GLfloat height;									//长,宽,高
	GLfloat angleX, angleZ;							//往+X方向与+Z方向的倾斜角
	GLfloat scaleX = 1, scaleY = 1, scaleZ = 1;		//各方向缩放比例
	void drawPrism();								//绘制单位棱柱
public:
	// 必传参数:传入二维点阵数组,顶点个数
	// 若不传入顶面多边形，则默认与底面相同
	Prism(GLfloat btmVertexArr[][2], int vertNum, GLfloat height = 1,GLfloat topVertexArr[][2] = NULL,
		GLfloat angleX = 0, GLfloat angleZ = 0, GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

	void setScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);

	void render();
};