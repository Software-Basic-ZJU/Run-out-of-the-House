#pragma once
#pragma execution_character_set("utf-8")
#include "Door.h"

Door::Door(GLfloat width, GLfloat height, GLfloat thickness,
	GLfloat x, GLfloat y, GLfloat z, GLfloat angle){
	this->width = width;
	this->height = height;
	this->thickness = thickness;
	this->x = x;
	this->y = y;
	this->z = z;
	this->angle = angle;

	this->door = new Cubic(width, thickness, height, 0, height / 2, 0);
}

void Door::setPosition(GLfloat x, GLfloat y, GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Door::rotateY(GLfloat angle){
	this->angle = angle;
}

void Door::render(){
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glRotatef(this->angle, 0, 1, 0);
	this->door->render();
	glPopMatrix();
}

