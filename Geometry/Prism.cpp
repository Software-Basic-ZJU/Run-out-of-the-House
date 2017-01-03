#include "Prism.h"

Prism::Prism(GLfloat vertexArr[][2],int vertNum,GLfloat height, GLfloat angleX, GLfloat angleZ,
	GLfloat x, GLfloat y, GLfloat z) :Geometry(x, y, z){
	GLfloat **vertexes = new GLfloat*[vertNum];
	for (int i = 0; i < vertNum; i++){
		vertexes[i] = new GLfloat[2];
		vertexes[i][0] = vertexArr[i][0];
		vertexes[i][1] = vertexArr[i][1];
	}
	this->vertexArr = vertexes;
	this->vertNum = vertNum;
	this->height = height;
	this->angleX = angleX;
	this->angleZ = angleZ;
}

void Prism::drawPrism(){
	int vertNum = this->vertNum;
	GLfloat offsetX = this->height*tan(this->angleX*PI / 180);		//x方向偏移量
	GLfloat offsetZ = this->height*tan(this->angleZ*PI / 180);		//y方向偏移量
	
	glBegin(GL_POLYGON);
	for (int index = 0; index < vertNum; index++){
		glVertex3f(this->vertexArr[index][0], 0, this->vertexArr[index][1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int index = 0; index < vertNum; index++){
		glVertex3f(offsetX + this->vertexArr[index][0], this->height, offsetZ + this->vertexArr[index][1]);
	}
	glEnd();

	for (int curr = 0; curr < vertNum; curr++){
		int next = curr + 1 < vertNum ? curr + 1 : 0;
		glBegin(GL_POLYGON);
		glVertex3f(this->vertexArr[curr][0], 0, this->vertexArr[curr][1]);
		glVertex3f(this->vertexArr[next][0], 0, this->vertexArr[next][1]);
		glVertex3f(offsetX + this->vertexArr[next][0], this->height, offsetZ + this->vertexArr[next][1]);
		glVertex3f(offsetX + this->vertexArr[curr][0], this->height, offsetZ + this->vertexArr[curr][1]);
		glEnd();
	}
}

void Prism::setScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ){
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
}

void Prism::render(){
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glRotatef(this->angle, this->rotX, this->rotY, this->rotZ);
	glScalef(this->scaleX, this->scaleY, this->scaleZ);
	this->drawPrism();
	glPopMatrix();
}