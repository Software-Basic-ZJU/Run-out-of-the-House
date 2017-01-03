#include "Sphere.h";

Sphere::Sphere(GLfloat radius, GLint M, GLint N, GLfloat x, GLfloat y, GLfloat z)
:Geometry(x,y,z){
	this->radius = radius;
	this->M = M;
	this->N = N;
}

void Sphere::drawSphere(){
	float step_z = PI / this->M;
	float step_xy = 2 * PI / this->N;
	float x[4], y[4], z[4];

	float angle_z = 0.0;
	float angle_xy = 0.0;
	int i = 0, j = 0;
	glBegin(GL_QUADS);
	for (i = 0; i<this->M; i++)
	{
		angle_z = i * step_z;

		for (j = 0; j<this->N; j++)
		{
			angle_xy = j * step_xy;

			x[0] = radius * sin(angle_z) * cos(angle_xy);
			y[0] = radius * sin(angle_z) * sin(angle_xy);
			z[0] = radius * cos(angle_z);

			x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
			y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
			z[1] = radius * cos(angle_z + step_z);

			x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);
			y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);
			z[2] = radius*cos(angle_z + step_z);

			x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
			y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
			z[3] = radius * cos(angle_z);

			for (int k = 0; k<4; k++)
			{
				glVertex3f(this->x + x[k], this->y + y[k], this->z + z[k]);
			}
		}
	}
	glEnd();
}

void Sphere::setRadius(GLfloat radius){
	this->radius = radius;
}

void Sphere::setMspice(GLfloat M){
	this->M = M;
}

void Sphere::setNspice(GLfloat N){
	this->N = N;
}

void Sphere::render(){
	if (this->hidden) return;

	glPushMatrix();
	//±ä»»
	glTranslatef(this->x, this->y, this->z);
	glScalef(this->radius, this->radius, this->radius);
	glRotatef(this->angle, this->rotX, this->rotY, this->rotZ);
	this->drawSphere();
	glPopMatrix();
}