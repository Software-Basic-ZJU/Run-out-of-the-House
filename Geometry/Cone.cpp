#include "Cone.h"

Cone::Cone(GLfloat radius, GLfloat height, GLint slice, GLfloat x, GLfloat y, GLfloat z)
:Geometry(x, y, z){
	this->radius = radius;
	this->height = height;
	this->slice = slice;
}

void Cone::drawCone(){
	GLfloat delta = 2 * PI / this->slice;
	GLint step;
	for (step = 0; step < this->slice; step++){
		glNormal3f(0, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex3f(0, 0, 0);
		glVertex3f(this->radius*cos(step*delta), 0, this->radius*sin(step*delta));
		glVertex3f(this->radius*cos((step + 1)*delta), 0, this->radius*sin((step + 1)*delta));
		glEnd();
	}

	for (step = 0; step < this->slice; step++){
		glNormal3f(this->radius*cos(step*delta), 0, this->radius*sin(step*delta));
		glBegin(GL_TRIANGLES);
		glVertex3f(this->radius*cos(step*delta), 0, this->radius*sin(step*delta));
		glVertex3f(0, 1, 0);
		glVertex3f(this->radius*cos((step + 1)*delta), 0, this->radius*sin((step + 1)*delta));
		glEnd();
	}
}

void Cone::render(){
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glScalef(this->radius, this->height, this->radius);
	glRotatef(this->angle,this->rotX, this->rotY, this->rotZ);
	this->drawCone();
	glPopMatrix();
}

