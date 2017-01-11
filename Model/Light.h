#pragma once
#include "prefix.h"

class Light {
private:
	int lightNum;
	GLfloat color[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[4] = {5, 5, 5, 0};
	GLfloat spotangle;				//�ü��Ƕ�
	GLfloat lightDir[3];			//��Դ����
	GLfloat agglomeration;			//�ۼ���
public:
	Light(int lightNum);
	~Light();
	void enable();
	void disable();
	void setAmbientLight();			//���û�����
	void setDiffuseLight();			//���ù�Դλ���Լ���������ɫ
	void setLimitRange();			//����λ���Թ�Դ���շ�Χ
	void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setColor(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setColor(GLfloat x, GLfloat y, GLfloat z);
	void setLightDir(GLfloat x, GLfloat y, GLfloat z);
	void setSpotangle(GLfloat x);
	void setAgglomeration(GLfloat x);
};