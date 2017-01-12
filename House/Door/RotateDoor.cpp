#pragma once
#pragma execution_character_set("utf-8")
#include "RotateDoor.h"

RotateDoor::RotateDoor(char *filename,GLTexture *texture,GLfloat width, GLfloat height, GLfloat thickness,
	GLfloat x, GLfloat y, GLfloat z, GLfloat angle,
	GLfloat speed, bool direction, bool status) :Door(width, height, thickness, x, y, z, angle){
	this->speed = speed;
	this->direction = direction;
	this->status = status;
	this->texture = texture;
	this->door = new ImportObj(filename);
	this->door->setTexture(texture);
	this->door->setPosition(0, 0, 0);
	this->door->setScalef(0.001*width, 0.001*height, 0.001*thickness);
	this->door->setRotatef(0, 0, 1, 0);
	if (status) this->fRotate = 90;
	else this->fRotate = 0;
}

void RotateDoor::setTexture(GLTexture *texture){
	this->door->setTexture(texture);
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
	glTranslatef(0.4*this->width*(-dir), 0, 0);
	glRotatef(this->fRotate*dir, 0, 1, 0);
	glTranslatef(0.4*this->width*dir, -0.55, 0);
	this->door->draw();
	glPopMatrix();
}