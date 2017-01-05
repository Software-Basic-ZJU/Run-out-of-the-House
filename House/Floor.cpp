#include "Floor.h";

Floor::Floor(GLfloat length, GLfloat width){
	this->length = length;
	this->width = width;
	this->mainFloor = new Cubic(length, width, 1, 0, -0.5, 0);

	//���ش�СӲ��Ϊ20*20
	this->entrance = new Cubic(21, 20, 1, -10, -0.5, 55);
}

void Floor::render(){
	this->mainFloor->render();
	this->entrance->render();
}

