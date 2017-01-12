#pragma once
#pragma execution_character_set("utf-8")
#include "ElectricFan.h"

ElectricFan::ElectricFan(GLfloat radius, GLfloat height,
	GLfloat x, GLfloat y, GLfloat z,GLfloat speed){
	this->radius = radius;
	this->height = height;
	this->x = x;
	this->y = y;
	this->z = z;
	this->fan = new ImportObj("House/ElectricFan/electricfan.obj");
	this->fan->setPosition(x, y, z);
	this->fan->setScalef(0.01*radius, 0.01*height, 0.01*radius);
	this->texture = new GLTexture;
	this->texture->Load("House/ElectricFan/flower2.bmp");
	this->fan->setTexture(this->texture);
	this->status = false;
	this->speed = speed;
	this->fRotate = 0;
}

void ElectricFan::setPosition(GLfloat x, GLfloat y, GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void ElectricFan::open(){
	this->status = true;
}

void ElectricFan::close(){
	this->status = false;
}

void ElectricFan::render(){
	if (this->status){			//´ò¿ª×´Ì¬
		this->fRotate += this->speed;
		if (this->fRotate > 360)
			this->fRotate = 0;
	}
	glPushMatrix();
	this->fan->setRotatef(this->fRotate, 0, 1, 0);
	this->fan->draw();
	glPopMatrix();
}