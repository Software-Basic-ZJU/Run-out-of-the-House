#include "Prism.h"

Prism::Prism(GLfloat btmVertexArr[][2],int vertNum,GLfloat height, GLfloat topVertexArr[][2],
	GLfloat angleX, GLfloat angleZ, GLfloat x, GLfloat y, GLfloat z) :Geometry(x, y, z){
	this->btmVertexArr = new GLfloat*[vertNum];
	if (topVertexArr != NULL)
		this->topVertexArr = new GLfloat*[vertNum];
	else
		this->topVertexArr = this->btmVertexArr;

	for (int i = 0; i < vertNum; i++){
		this->btmVertexArr[i] = new GLfloat[2];
		this->btmVertexArr[i][0] = btmVertexArr[i][0];
		this->btmVertexArr[i][1] = btmVertexArr[i][1];
		if (topVertexArr != NULL){
			this->topVertexArr[i] = new GLfloat[2];
			this->topVertexArr[i][0] = topVertexArr[i][0];
			this->topVertexArr[i][1] = topVertexArr[i][1];
		}
	}
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
		glVertex3f(this->btmVertexArr[index][0], 0, this->btmVertexArr[index][1]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int index = 0; index < vertNum; index++){
		glVertex3f(offsetX + this->topVertexArr[index][0], this->height, offsetZ + this->topVertexArr[index][1]);
	}
	glEnd();

	for (int curr = 0; curr < vertNum; curr++){
		int next = curr + 1 < vertNum ? curr + 1 : 0;
		glBegin(GL_POLYGON);
		glVertex3f(this->btmVertexArr[curr][0], 0, this->btmVertexArr[curr][1]);
		glVertex3f(this->btmVertexArr[next][0], 0, this->btmVertexArr[next][1]);
		glVertex3f(offsetX + this->topVertexArr[next][0], this->height, offsetZ + this->topVertexArr[next][1]);
		glVertex3f(offsetX + this->topVertexArr[curr][0], this->height, offsetZ + this->topVertexArr[curr][1]);
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