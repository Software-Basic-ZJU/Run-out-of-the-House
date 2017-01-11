#pragma once
#include "prefix.h"

class Light {
private:
	int lightNum;
	GLfloat color[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[4] = {5, 5, 5, 0};
	GLfloat spotangle;				//裁减角度
	GLfloat lightDir[3];			//光源方向
	GLfloat agglomeration;			//聚集度
public:
	Light(int lightNum);
	~Light();
	void enable();
	void disable();
	void setAmbientLight();			//设置环境光
	void setDiffuseLight();			//设置光源位置以及漫反射颜色
	void setLimitRange();			//设置位置性光源光照范围
    void setPosition();
	void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setColor(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setColor(GLfloat x, GLfloat y, GLfloat z);
	void setLightDir(GLfloat x, GLfloat y, GLfloat z);
	void setSpotangle(GLfloat x);
	void setAgglomeration(GLfloat x);
};