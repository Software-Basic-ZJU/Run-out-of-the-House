#pragma once
#pragma execution_character_set("utf-8")
#include "Table.h"

Table::Table(GLfloat length, GLfloat width, GLfloat height,
	GLfloat x, GLfloat y, GLfloat z, GLfloat angle){
	this->length = length;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->z = z;
	this->angle = angle;

	Cubic *desktop = new Cubic(length, width, 0.5, 0, height/2, 0);
	Cubic *leg1 = new Cubic(0.5, 0.5, height - 0.25, 0.3*length, 0, 0.3*width);
	Cubic *leg2 = new Cubic(0.5, 0.5, height - 0.25,  -0.3*length, 0, 0.3*width);
	Cubic *leg3 = new Cubic(0.5, 0.5, height - 0.25, 0.3*length, 0, -0.3*width);
	Cubic *leg4 = new Cubic(0.5, 0.5, height - 0.25, -0.3*length, 0, -0.3*width);

	this->geoList.push_back(desktop);
	this->geoList.push_back(leg1);
	this->geoList.push_back(leg2);
	this->geoList.push_back(leg3);
	this->geoList.push_back(leg4);
}

void Table::setPosition(GLfloat x, GLfloat y, GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Table::setTexture(GLTexture *texture){
	for (list<Geometry *>::iterator geo = geoList.begin();
		geo != geoList.end(); geo++){
		(*geo)->setTexture(texture);
	}
}

void Table::rotateY(GLfloat angle){
	this->angle = angle;
}

void Table::render(){
	glPushMatrix();
	glTranslatef(this->x, this->y + this->height / 2, this->z);
	glRotatef(this->angle, 0, 1, 0);
	for (list<Geometry *>::iterator geo = this->geoList.begin();
		geo != this->geoList.end(); geo++){
		(*geo)->render();
	}
	glPopMatrix();
}