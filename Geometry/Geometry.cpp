#include "Geometry.h"

Geometry::Geometry(GLfloat x, GLfloat y,GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
	this->angle = 0;
	this->hidden = false;
}

void Geometry::rotateX(GLfloat angle){
	this->angle = angle;
	this->rotX = 1;
	this->rotY = 0;
	this->rotZ = 0;
}

void Geometry::rotateY(GLfloat angle){
	printf("Y angle:%f", angle);
	this->angle = angle;
	this->rotX = 0;
	this->rotY = 1;
	this->rotZ = 0;
}

void Geometry::rotateZ(GLfloat angle){
	this->angle = angle;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 1;
}

void Geometry::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z){
	this->angle;
	this->rotX = x;
	this->rotY = y;
	this->rotZ = z;
}

void Geometry::setPosition(GLfloat x, GLfloat y, GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Geometry::isHide(bool hidden){
	this->hidden = hidden;
}
