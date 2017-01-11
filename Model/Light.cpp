#include "Light.h"

Light::Light(int lightNum)
{
	this->lightNum = lightNum;
}

Light::~Light()
{
	this->disable();
}

void Light::enable()
{
	glEnable(this->lightNum);
}

void Light::disable()
{
	glDisable(this->lightNum);
}

void Light::setAmbientLight()
{
	glLightfv(this->lightNum, GL_AMBIENT, this->color);
}

void Light::setDiffuseLight()
{
	glLightfv(this->lightNum, GL_POSITION, this->position);
	glLightfv(this->lightNum, GL_DIFFUSE, this->color);
}

//���ƹ��շ�Χ���ﵽ�۹�Ƶ�Ч�����ú���ֻ��λ���Թ�Դ��Ч
void Light::setLimitRange()
{
	glLightf(this->lightNum, GL_SPOT_CUTOFF, this->spotangle);             //�ü��Ƕ�
	glLightfv(this->lightNum, GL_SPOT_DIRECTION, this->lightDir);          //��Դ����
	glLightf(this->lightNum, GL_SPOT_EXPONENT, this->agglomeration);       //�ۼ���
}

//WΪ0�Ƿ����Թ�Դ(̫����);W��Ϊ����λ���Թ�Դ,X/W, Y/W, Z/W��ʾ�˹�Դ��λ��
void Light::setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	this->position[0] = x;
	this->position[1] = y;
	this->position[2] = z;
	this->position[3] = w;
}

void Light::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	this->position[0] = x;
	this->position[1] = y;
	this->position[2] = z;
}

//���ĸ�����W�ǹ���ǿ��
void Light::setColor(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	this->color[0] = x;
	this->color[1] = y;
	this->color[2] = z;
	this->color[3] = w;
}

void Light::setColor(GLfloat x, GLfloat y, GLfloat z)
{
	this->color[0] = x;
	this->color[1] = y;
	this->color[2] = z;
}

//����(x,y,z)�ǹ�Դ����ķ���
void Light::setLightDir(GLfloat x, GLfloat y, GLfloat z)
{
	this->lightDir[0] = x;
	this->lightDir[1] = y;
	this->lightDir[2] = z;
}

/*
spotangle��ʾһ���Ƕȣ����ǹ�Դ������������ǽǶȵ�һ��
spotangle��[0,90]��{180}
spotangle=180:ȫ��Χ���䣬��ʹ�þ۹��
*/
void Light::setSpotangle(GLfloat x)
{
	this->spotangle = x;
}

/*
agglomeration��ʾ�۹�ĳ̶ȣ�
Ϊ��ʱ��ʾ���շ�Χ�����������Ĺ���ǿ����ͬ��
Ϊ����ʱ��ʾ���������뼯�У����Է��䷽���λ���ܵ�������գ�����λ���ܵ����ٹ��ա���ֵԽ�󣬾۹�Ч����Խ���ԡ�
*/
void Light::setAgglomeration(GLfloat x)
{
	this->agglomeration = x;
}
