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
	glLightfv(this->lightNum, GL_DIFFUSE, this->color);
}

//限制光照范围，达到聚光灯的效果，该函数只对位置性光源有效
void Light::setLimitRange()
{
	glLightf(this->lightNum, GL_SPOT_CUTOFF, this->spotangle);             //裁减角度
	glLightfv(this->lightNum, GL_SPOT_DIRECTION, this->lightDir);          //光源方向
	glLightf(this->lightNum, GL_SPOT_EXPONENT, this->agglomeration);       //聚集度
}

void Light::setPosition()
{
    glLightfv(this->lightNum, GL_POSITION, this->position);
}

//W为0是方向性光源(太阳光);W不为零是位置性光源,X/W, Y/W, Z/W表示了光源的位置
void Light::setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	this->position[0] = x;
	this->position[1] = y;
	this->position[2] = z;
	this->position[3] = w;
    glLightfv(this->lightNum, GL_POSITION, this->position);
}

void Light::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	this->position[0] = x;
	this->position[1] = y;
	this->position[2] = z;
    glLightfv(this->lightNum, GL_POSITION, this->position);
}

//第四个参数W是光照强度
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

//向量(x,y,z)是光源发射的方向
void Light::setLightDir(GLfloat x, GLfloat y, GLfloat z)
{
	this->lightDir[0] = x;
	this->lightDir[1] = y;
	this->lightDir[2] = z;
}

/*
spotangle表示一个角度，它是光源发射光线所覆盖角度的一半
spotangle∈[0,90]∪{180}
spotangle=180:全周围发射，不使用聚光灯
*/
void Light::setSpotangle(GLfloat x)
{
	this->spotangle = x;
}

/*
agglomeration表示聚光的程度，
为零时表示光照范围内向各方向发射的光线强度相同，
为正数时表示光照向中央集中，正对发射方向的位置受到更多光照，其它位置受到较少光照。数值越大，聚光效果就越明显。
*/
void Light::setAgglomeration(GLfloat x)
{
	this->agglomeration = x;
}
