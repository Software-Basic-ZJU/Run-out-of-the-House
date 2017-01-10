#pragma once
#include "GLTexture.h"

class ImportObj{
private:
	GLTexture* texture;
	GLfloat scalef[3];
	GLfloat translatef[3];
	GLfloat rotatef[4];
	vector<VERTEX> vertex_list;
	vector<FACE> face_list;
	int vertex_count, face_count;
	void calculateNormal(float *out, float *a, float *b, float *c);
	void calculateNormals(void);
public:
	ImportObj(char* filename);
	~ImportObj(void);
	void draw();
	void setTexture(GLTexture* text);
	void setScalef(GLfloat x,GLfloat y,GLfloat z);
	void setTranslatef(GLfloat x, GLfloat y, GLfloat z);
	void setRotatef(GLfloat angel, GLfloat x, GLfloat y, GLfloat z);
};
