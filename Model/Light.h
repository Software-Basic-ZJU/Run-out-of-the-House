#pragma once
#include "prefix.h"

class Light {
private:
	GLfloat color[4];
	GLfloat position[4];
	int lightNum;
	GLfloat spotangle;				//裁减角度
	GLfloat lightDir[3];			//光源方向
	GLfloat agglomeration;			//聚集度
public:
	Light(int lightNum);
	~Light();
	void enable();
	void disable();
	void setSpecular();				//设置镜面光
	void setAmbientLight();			//设置环境光
	void setDiffuseLight();			//设置漫反射颜色
	void setLimitRange();			//设置位置性光源光照范围
    void setPosition();
	void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 0);
	void setColor(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1);
	void setLightDir(GLfloat x, GLfloat y, GLfloat z);
	void setSpotangle(GLfloat x);
	void setAgglomeration(GLfloat x);
};