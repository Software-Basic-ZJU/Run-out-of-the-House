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
	GLfloat texInit = 0;							//绘制纹理起点
	GLfloat texStep = 1 / (GLfloat)this->slice;		//绘制纹理步长

	for (; step < this->slice; step++){
		glBegin(GL_QUADS);
		//draw top circle
		glNormal3f(0, 0.5, 0);
		glTexCoord2f(texInit, 0);
		glVertex3f(0, 0.5, 0);
		glTexCoord2f(texInit, 1);
		glVertex3f(1*cos(step*delta), 0.5, 1*sin(step*delta));
		glTexCoord2f(texInit + texStep, 1);
		glVertex3f(1*cos((step + 1)*delta), 0.5, 1*sin((step + 1)*delta));
		glTexCoord2f(texInit + texStep, 0);
		glVertex3f(0, 0.5, 0);
		glEnd();

		glBegin(GL_QUADS);
		//draw bottom circle
		glNormal3f(0, -0.5, 0);
		glTexCoord2f(texInit, 0);
		glVertex3f(0, -0.5, 0);
		glTexCoord2f(texInit, 1);
		glVertex3f(1 * cos(step*delta), -0.5, 1 * sin(step*delta));
		glTexCoord2f(texInit + texStep, 1);
		glVertex3f(1 * cos((step + 1)*delta), -0.5, 1 * sin((step + 1)*delta));
		glTexCoord2f(texInit + texStep, 0);
		glVertex3f(0, -0.5, 0);
		glEnd();

		//draw cylinder
		glBegin(GL_QUADS);
		glNormal3f(1*cos(step*delta), 0.5, 1*sin(step*delta));
		glTexCoord2f(texInit + texStep, 1);
		glVertex3f(1 * cos(step*delta), 0.5, 1 * sin(step*delta));
		glTexCoord2f(texInit, 1);
		glVertex3f(1 * cos((step + 1)*delta), 0.5, 1 * sin((step + 1)*delta));
		glTexCoord2f(texInit, 0);
		glVertex3f(1*cos((step + 1)*delta), -0.5, 1*sin((step + 1)*delta));
		glTexCoord2f(texInit + texStep, 0);
		glVertex3f(1 * cos(step*delta), -0.5, 1 * sin(step*delta));
		glEnd();

		texInit += texStep;
	}
}

void Cylinder::render(){
	if (this->texture) texture->mount();
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glScalef(this->radius, this->height, this->radius);
	glRotatef(this->angle, this->rotX, this->rotY, this->rotZ);
	this->drawCylinder();
	glPopMatrix();
	if (this->texture) texture->unmount();
}