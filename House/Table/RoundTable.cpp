#pragma once
#pragma execution_character_set("utf-8")
#include "RoundTable.h"

RoundTable::RoundTable(GLfloat radius, GLfloat height, GLfloat x, GLfloat y, GLfloat z, GLfloat angle){
	this->radius = radius;
	this->height = height;
	this->x = x;
	this->y = y;
	this->z = z;
	this->angle = angle;
	this->texture = NULL;
	Cylinder *desktop = new Cylinder(radius, 0.5, 200, 0, height + 0.25, 0);

	//����Ĭ�ϰ뾶Ϊ1
	GLfloat legDist = radius * 0.618;					//���Ⱦ���Բ�ĵľ���
	Cylinder *leg1 = new Cylinder(0.3, height, 100, 0, height / 2, -legDist);
	Cylinder *leg2 = new Cylinder(0.3, height, 100, -legDist*cos(30 * PI / 180), height / 2, legDist*sin(30 * PI / 180));
	Cylinder *leg3 = new Cylinder(0.3, height, 100, legDist*cos(30 * PI / 180), height / 2, legDist*sin(30 * PI / 180));

	this->geoList.push_back(desktop);
	this->geoList.push_back(leg1);
	this->geoList.push_back(leg2);
	this->geoList.push_back(leg3);
}

void RoundTable::setTexuture(GLTexture *texture){
	this->texture = texture;
}

void RoundTable::rotateY(GLfloat angle){
	this->angle = angle;
}

void RoundTable::setPosition(GLfloat x, GLfloat y, GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void RoundTable::render(){
	if (this->texture) texture->mount();
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(this->angle, 0, 1, 0);
	for (list<Geometry *>::iterator geo = this->geoList.begin();
		geo != this->geoList.end(); geo++){
		(*geo)->render();
	}
	glPopMatrix();
	if (this->texture) texture->unmount();
}