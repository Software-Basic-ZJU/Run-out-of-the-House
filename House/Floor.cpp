#include "Floor.h";

Floor::Floor(GLfloat length, GLfloat width){
	this->length = length;
	this->width = width;
	Cubic *cubic = new Cubic(length, width, 1, 0, -0.5, 0);
	this->geoList.push_back(cubic);
}

void Floor::render(){
	for (list<Geometry*>::iterator geo = this->geoList.begin();
		geo != this->geoList.end(); geo++){
		(*geo)->render();
	}
}

