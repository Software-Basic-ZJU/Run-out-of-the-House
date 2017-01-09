#pragma once
#pragma execution_character_set("utf-8")
#include "Bed.h"

Bed::Bed(GLfloat length, GLfloat width, GLfloat height,
	GLfloat x,GLfloat y,GLfloat z, GLfloat angle){
	this->length = length;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->z = z;
	this->angle = angle;

	//��ͷ1
	Cubic *pillow1 = new Cubic(0.15*length, 0.4*width, 0.4, 0.2*length, height + 2.2, -0.25*width);

	//��ͷ2
	Cubic *pillow2 = new Cubic(0.15*length, 0.4*width, 0.4, 0.2*length, height + 2.2, 0.25*width);

	//����
	Cubic *bedBody = new Cubic(length, width, 2, 0, height + 1, 0);

	//��ͷ
	Cubic *bedHead = new Cubic(0.2*length, width, 0.8, 0.4*length, height + 2.4, 0);

	//����
	Cubic *leg1 = new Cubic(1, 1, height, -length / 2 + 0.5, height/2, -width / 2 + 0.5);
	Cubic *leg2 = new Cubic(1, 1, height, length / 2 - 0.5, height / 2, -width / 2 + 0.5);
	Cubic *leg3 = new Cubic(1, 1, height, length / 2 - 0.5, height / 2, width / 2 - 0.5);
	Cubic *leg4 = new Cubic(1, 1, height, -length / 2 + 0.5, height / 2, width / 2 - 0.5);

	this->geoList.push_back(pillow1); 
	this->geoList.push_back(pillow2);
	this->geoList.push_back(bedBody);
	this->geoList.push_back(bedHead);
	this->geoList.push_back(leg1);
	this->geoList.push_back(leg2);
	this->geoList.push_back(leg3);
	this->geoList.push_back(leg4);

}

void Bed::rotateY(GLfloat angle){
	this->angle = angle;
}

void Bed::setPosition(GLfloat x, GLfloat y, GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Bed::render(){
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glRotatef(this->angle, 0, 1, 0);
	for (list<Geometry *>::iterator geo = this->geoList.begin();
		geo != this->geoList.end(); geo++){
		(*geo)->render();
	}
	glPopMatrix();
}