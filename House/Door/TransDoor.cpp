#pragma once
#pragma execution_character_set("utf-8")
#include "TransDoor.h"

TransDoor::TransDoor(GLfloat width, GLfloat height, GLfloat thickness,
	GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
	GLfloat speed, bool direction, bool status) :Door(width, height, thickness, x, y, z, angle){
	this->speed = speed;
	this->direction = direction;
	this->status = status;

	if (status) this->disappear = 0.1;
	else this->disappear = 1;
}

bool TransDoor::getStatus(){
	return this->status;
}

void TransDoor::openDoor(){
	this->status = true;
}

void TransDoor::closeDoor(){
	this->status = false;
}

void TransDoor::render(){
	if (status && disappear < 1) disappear += speed;
	if (!status && disappear > 0) disappear -= speed;
	int dir = this->direction ? -1 : 1;
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glRotatef(this->angle, 0, 1, 0);
	glTranslatef(this->disappear*0.5*this->width*dir, 0, 0);
	this->door->resize(this->width*(1 - this->disappear), this->thickness, this->height);
	this->door->render();
	glPopMatrix();
}