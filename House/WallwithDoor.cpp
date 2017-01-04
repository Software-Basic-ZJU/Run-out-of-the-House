#pragma once
#pragma execution_character_set("utf-8")
#include "WallwithDoor.h"

WallwithDoor::WallwithDoor(GLfloat length, GLfloat width, GLfloat doorLen, GLfloat doorHei,
	GLfloat x, GLfloat y, GLfloat z){
	this->length = length;
	this->width = width;
	this->doorLen = doorLen;
	this->doorHei = doorHei;
	this->x = x;
	this->y = y;
	this->z = z;

	// 沿x方向的墙
	if (length > width){
		this->ltCubic = new Cubic((length - doorLen) / 2, width, this->height,
			x - length / 4 - doorLen / 4, y + this->height / 2, z);
		this->rtCubic = new Cubic((length - doorLen) / 2, width, this->height,
			x + length / 4 + doorLen / 4, this->y + this->height / 2, z);
		this->topCubic = new Cubic(doorLen, width, this->height - this->doorHei,x,y+(this->doorHei+this->height)/2,z);
	}
	// 沿z方向的墙
	else{
		this->ltCubic = new Cubic(length, (width - doorLen) / 2, this->height,
			x, y + this->height / 2, z - width / 4 - doorLen / 4);
		this->rtCubic = new Cubic(length, (width - doorLen) / 2, this->height,
			x, this->y + this->height / 2, z + width / 4 + doorLen / 4);
		this->topCubic = new Cubic(length, doorLen, this->height - this->doorHei, x, y + (this->doorHei + this->height) / 2, z);
	}
		
}

void WallwithDoor::setPosition(GLfloat x, GLfloat y, GLfloat z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void WallwithDoor::render(){
	this->ltCubic->render();
	this->rtCubic->render();
	this->topCubic->render();
}