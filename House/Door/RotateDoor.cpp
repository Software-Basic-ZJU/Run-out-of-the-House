#pragma once
#pragma execution_character_set("utf-8")
#include "RotateDoor.h"

RotateDoor::RotateDoor(GLfloat width, GLfloat height, GLfloat thickness,
	GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
	GLfloat speed, bool direction, bool status) :Door(width, height, thickness, x, y, z, angle){
	this->speed = speed;
	this->direction = direction;
	this->status = status;
	if (status) this->fRotate = 90;
	else this->fRotate = 0;
}

bool RotateDoor::getStatus(){
	return this->status;
}

void RotateDoor::openDoor(){
	this->status = true;
}

void RotateDoor::closeDoor(){
	this->status = false;
}

void RotateDoor::render(){
	int dir = this->direction ? 1 : -1;
	if (this->status && this->fRotate <= 90){			//开门
		this->fRotate += this->speed;
	}
	if (!this->status && this->fRotate >= 0){			//关门
		this->fRotate -= this->speed;
	}
	glPushMatrix();
	glTranslatef(this->x, this->y + 0.5, this->z);
	glRotatef(this->angle, 0, 1, 0);
	glTranslatef(0.5*this->width*(-dir), 0, 0);
	glRotatef(this->fRotate*dir, 0, 1, 0);
	glTranslatef(0.5*this->width*dir, -0.55, 0);
	this->door->render();
	glPopMatrix();
}