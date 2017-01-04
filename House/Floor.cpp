#include "Floor.h";

Floor::Floor(GLfloat length, GLfloat width){
	this->length = length;
	this->width = width;
	Cubic *cubic = new Cubic(length, width, 1, 0, -0.5, 0);
	this->cubic = cubic;
}

void Floor::render(){
	this->cubic->render();
}

