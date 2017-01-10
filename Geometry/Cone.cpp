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
	GLfloat texInit = 0;							//绘制纹理的起点
	GLfloat texStep = 1 / (GLfloat)this->slice;		//绘制纹理的步长

	//底面圆
	for (step = 0, texInit = 0; step < this->slice; step++){
		glNormal3f(0, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(texInit, 0.0);
		glVertex3f(0, 0, 0);
		glTexCoord2f(texInit, 1.0);
		glVertex3f(this->radius*cos(step*delta), 0, this->radius*sin(step*delta));
		glTexCoord2f(texInit + texStep, 1.0);
		glVertex3f(this->radius*cos((step + 1)*delta), 0, this->radius*sin((step + 1)*delta));
		glTexCoord2f(texInit + texStep, 0.0);
		glVertex3f(0, 0, 0);
		glEnd();
		texInit += texStep;
	}

	//侧面圆
	for (step = 0, texInit = 0; step < this->slice; step++){
		glNormal3f(this->radius*cos(step*delta), 0, this->radius*sin(step*delta));
		glBegin(GL_QUADS);
		glTexCoord2f(texInit, 0.0);
		glVertex3f(0, 1, 0);
		glTexCoord2f(texInit, 1.0);
		glVertex3f(this->radius*cos((step + 1)*delta), 0, this->radius*sin((step + 1)*delta));
		glTexCoord2f(texInit + texStep, 1.0);
		glVertex3f(this->radius*cos(step*delta), 0, this->radius*sin(step*delta));
		glTexCoord2f(texInit + texStep, 0.0);
		glVertex3f(0, 1, 0);
		glEnd();
		texInit += texStep;
	}
	
}

void Cone::render(){
	if (this->texture) texture->mount();			//使用纹理
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glScalef(this->radius, this->height, this->radius);
	glRotatef(this->angle,this->rotX, this->rotY, this->rotZ);
	this->drawCone();
	glPopMatrix();
	if (this->texture) texture->unmount();

}

