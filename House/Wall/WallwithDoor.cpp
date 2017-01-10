#pragma once
#pragma execution_character_set("utf-8")
#include "WallwithDoor.h"

WallwithDoor::WallwithDoor(GLfloat length, GLfloat width, GLfloat doorWidth, GLfloat doorHei,
	GLfloat x, GLfloat y, GLfloat z,GLfloat angle){
	this->length = length;
	this->width = width;
	this->doorWidth = doorWidth;
	this->doorHei = doorHei;
	this->x = x;
	this->y = y;
	this->z = z;
	this->angle = angle;
	this->ltCubic = new Cubic((length - doorWidth) / 2, width, this->height,
		- length / 4 - doorWidth / 4, this->height / 2, 0);
	this->rtCubic = new Cubic((length - doorWidth) / 2, width, this->height,
		length / 4 + doorWidth / 4, this->height / 2, 0);
	this->topCubic = new Cubic(doorWidth, width, this->height - this->doorHei,
		0,(this->doorHei+this->height)/2,0);
		
}

void WallwithDoor::setPosition(GLfloat x, GLfloat y, GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void WallwithDoor::setTexture(GLTexture *texture){
	this->ltCubic->setTexture(texture);
	this->rtCubic->setTexture(texture);
	this->topCubic->setTexture(texture);
}

void WallwithDoor::rotateY(GLfloat angle){
	this->angle = angle;
}

void WallwithDoor::render(){
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glRotatef(this->angle, 0, 1, 0);
	this->ltCubic->render();
	this->rtCubic->render();
	this->topCubic->render();
	glPopMatrix();
}