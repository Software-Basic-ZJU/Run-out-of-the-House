#include "Cylinder.h"

Cylinder::Cylinder(GLfloat radius, GLfloat height, GLint slice , GLfloat x,GLfloat y,GLfloat z)
:Geometry(x,y,z){
	this->radius = radius;
	this->height = height;
	this->slice = slice;
}

void Cylinder::drawCylinder(){
	GLint step = 0;
	GLfloat delta = 2 * PI / this->slice;
	for (; step < this->slice; step++){
		glBegin(GL_TRIANGLES);
		//draw top circle
		glVertex3f(0, 0.5, 0);
		glVertex3f(this->radius*cos(step*delta), 0.5, this->radius*sin(step*delta));
		glVertex3f(this->radius*cos((step + 1)*delta), 0.5, this->radius*sin((step + 1)*delta));
		glEnd();

		glBegin(GL_TRIANGLES);
		//draw bottom circle
		glVertex3f(0, -0.5, 0);
		glVertex3f(this->radius*cos(step*delta), -0.5, this->radius*sin(step*delta));
		glVertex3f(this->radius*cos((step + 1)*delta), -0.5, this->radius*sin((step + 1)*delta));
		glEnd();

		//draw cylinder
		glBegin(GL_QUADS);
		glVertex3f(this->radius*cos(step*delta), 0.5, this->radius*sin(step*delta));
		glVertex3f(this->radius*cos((step + 1)*delta), 0.5, this->radius*sin((step + 1)*delta));
		glVertex3f(this->radius*cos((step + 1)*delta), -0.5, this->radius*sin((step + 1)*delta));
		glVertex3f(this->radius*cos(step*delta), -0.5, this->radius*sin(step*delta));

		glEnd();
	}
}

void Cylinder::render(){
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glScalef(this->radius, this->height, this->radius);
	glRotatef(this->angle, this->rotX, this->rotY, this->rotZ);
	this->drawCylinder();
	glPopMatrix();
}