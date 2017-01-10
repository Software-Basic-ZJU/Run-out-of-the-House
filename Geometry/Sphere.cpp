#include "Sphere.h";

Sphere::Sphere(GLfloat radius, GLint M, GLint N, GLfloat x, GLfloat y, GLfloat z)
:Geometry(x,y,z){
	this->radius = radius;
	this->M = M;
	this->N = N;
}

void Sphere::drawSphere(){
	GLfloat step_z = PI / this->M;
	GLfloat step_xy = 2 * PI / this->N;
	GLfloat x[4], y[4], z[4], texCoor[4][2];

	GLfloat angle_z = 0.0;
	GLfloat angle_xy = 0.0;
	GLint i = 0, j = 0;

	GLfloat xInit = 0, yInit = 0;		//横纵向纹理初始值
	GLfloat mStep = 1 / (GLfloat)M;		//横向纹理绘制步长
	GLfloat nStep = 1 / (GLfloat)N;		//纵向纹理绘制步长
	glBegin(GL_QUADS);
	glShadeModel(GL_FLAT);
	for (i = 0; i<this->M; i++)
	{
		angle_z = i * step_z;

		for (j = 0; j<this->N; j++)
		{
			angle_xy = j * step_xy;

			x[0] = radius * sin(angle_z) * cos(angle_xy);
			y[0] = radius * sin(angle_z) * sin(angle_xy);
			z[0] = radius * cos(angle_z);
			texCoor[0][0] = xInit;
			texCoor[0][1] = yInit;

			x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
			y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
			z[1] = radius * cos(angle_z + step_z);
			texCoor[1][0] = xInit;
			texCoor[1][1] = yInit + nStep;

			x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);
			y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);
			z[2] = radius*cos(angle_z + step_z);
			texCoor[2][0] = xInit + mStep;
			texCoor[2][1] = yInit + nStep;

			x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
			y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
			z[3] = radius * cos(angle_z);
			texCoor[3][0] = xInit + mStep;
			texCoor[3][1] = yInit;

			for (int k = 0; k<4; k++)
			{
				glTexCoord2f(texCoor[k][0], texCoor[k][1]);
				glVertex3f(x[k], y[k], z[k]);
				glNormal3f(x[k], y[k], z[k]);
			}
			yInit += nStep;
		}
		xInit += mStep;

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
	if (this->texture) texture->mount();
	glPushMatrix();
	//变换
	glTranslatef(this->x, this->y, this->z);
	glScalef(this->radius, this->radius, this->radius);
	glRotatef(this->angle, this->rotX, this->rotY, this->rotZ);
	this->drawSphere();
	glPopMatrix();
	if (this->texture) texture->unmount();

}