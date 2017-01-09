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

	Cylinder *desktop = new Cylinder(radius, 0.5, 200, 0, height + 0.25, 0);

	//×ÀÍÈÄ¬ÈÏ°ë¾¶Îª1
	GLfloat legDist = radius * 0.618;					//×ÀÍÈ¾àÀëÔ²ÐÄµÄ¾àÀë
	Cylinder *leg1 = new Cylinder(0.3, height, 100, 0, height / 2, -legDist);
	Cylinder *leg2 = new Cylinder(0.3, height, 100, -legDist*cos(30 * PI / 180), height / 2, legDist*sin(30 * PI / 180));
	Cylinder *leg3 = new Cylinder(0.3, height, 100, legDist*cos(30 * PI / 180), height / 2, legDist*sin(30 * PI / 180));

	this->geoList.push_back(desktop);
	this->geoList.push_back(leg1);
	this->geoList.push_back(leg2);
	this->geoList.push_back(leg3);
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
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(this->angle, 0, 1, 0);
	for (list<Geometry *>::iterator geo = this->geoList.begin();
		geo != this->geoList.end(); geo++){
		(*geo)->render();
	}
	glPopMatrix();
}