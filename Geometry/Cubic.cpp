#include "Cubic.h"

GLfloat Cubic::cubic[8][3] = {			//单位立方体坐标点
	{ 0.5, 0.5, 0.5 },
	{ 0.5, 0.5, -0.5 },
	{ -0.5, 0.5, -0.5 },
	{ -0.5, 0.5, 0.5 },
	{ 0.5, -0.5, 0.5 },
	{ 0.5, -0.5, -0.5 },
	{ -0.5, -0.5, -0.5 },
	{ -0.5, -0.5, 0.5 }
};
GLint Cubic::cubicIndex[6][4] = {		//各面顶点坐标索引
	{ 0, 1, 2, 3 },
	{ 4, 5, 6, 7 },
	{ 0, 1, 5, 4 },
	{ 2, 3, 7, 6 },
	{ 3, 0, 4, 7 },
	{ 1, 2, 6, 5 }
};

Cubic::Cubic(GLfloat length, GLfloat width, GLfloat height,
	GLfloat x, GLfloat y, GLfloat z):Geometry(x, y, z){
	this->length = length;
	this->width = width;
	this->height = height;
}

void Cubic::drawCubic(){
	int i, j, k;

	glBegin(GL_QUADS);
	for (i = 0; i < 6; i++){
		glNormal3f(cubic[cubicIndex[i][0]][0],
			cubic[cubicIndex[i][0]][1],
			cubic[cubicIndex[i][0]][2]);
		for (j = 0, k = 0; j<4; j++, k++){
			if (k>4) k = 0;
			glTexCoord2f(textCoor[k][0], textCoor[k][1]);
			glVertex3f(cubic[cubicIndex[i][j]][0],
				cubic[cubicIndex[i][j]][1],
				cubic[cubicIndex[i][j]][2]);
		}
	}
	glEnd();
	glFlush();
}

void Cubic::resize(GLfloat length, GLfloat width, GLfloat height){
	this->length = length;
	this->width = width;
	this->height = height;
}

void Cubic::render(){
	if (this->hidden) return;
	if (this->texture) texture->mount();			//使用纹理
	glPushMatrix();
	//变换
	glTranslatef(this->x, this->y, this->z);
	glScalef(length, height, width);
	glRotatef(this->angle, this->rotX, this->rotY, this->rotZ);
	this->drawCubic();
	glPopMatrix();
	if (this->texture) texture->unmount();

}