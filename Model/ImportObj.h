#pragma once
#include "GLTexture.h"

class ImportObj{
private:
	GLTexture* texture;							//纹理
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
	void setTexture(GLTexture* text);										//设置纹理
	void setScalef(GLfloat x,GLfloat y,GLfloat z);							//设置缩放
	void setPosition(GLfloat x, GLfloat y, GLfloat z);						//设置位置
	void setRotatef(GLfloat angel, GLfloat x, GLfloat y, GLfloat z);		//设置绕某轴旋转
};
