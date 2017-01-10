#pragma once
#pragma execution_character_set("utf-8")
#include "Wall.h"

Wall::Wall(GLfloat length, GLfloat width,
	GLfloat x,GLfloat y,GLfloat z){
	this->lenth = length;
	this->width = width;
	this->x = x;
	this->y = y;
	this->z = z;
	//默认墙的底面在y=0平面上
	Cubic *cubic = new Cubic(length, width, this->height, x, y + this->height / 2, z);
	this->cubic = cubic;
}

void Wall::setPosition(GLfloat x, GLfloat y, GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
	this->cubic->setPosition(x, y, z);
}

void Wall::setTexture(GLTexture *texture){
	this->cubic->setTexture(texture);
}

void Wall::render(){
	this->cubic->render();
}