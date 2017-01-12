#pragma once
#include "prefix.h"

class Light {
private:
	GLfloat color[4];
	GLfloat position[4];
	int lightNum;
	GLfloat spotangle;				//�ü��Ƕ�
	GLfloat lightDir[3];			//��Դ����
	GLfloat agglomeration;			//�ۼ���
public:
	Light(int lightNum);
	~Light();
	void enable();
	void disable();
	void setSpecular();				//���þ����
	void setAmbientLight();			//���û�����
	void setDiffuseLight();			//������������ɫ
	void setLimitRange();			//����λ���Թ�Դ���շ�Χ
    void setPosition();
	void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 0);
	void setColor(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1);
	void setLightDir(GLfloat x, GLfloat y, GLfloat z);
	void setSpotangle(GLfloat x);
	void setAgglomeration(GLfloat x);
};